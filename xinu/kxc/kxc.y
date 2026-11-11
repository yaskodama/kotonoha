/* kxc.y - Xinu の中で動くことのはのコンパイラの文法（構文木を作る）
 *
 * 規則は ../../kotonoha.y（一文方式・厳格版）と同じ。違うのは動作だけで、構造化形式の文字列の代わりに
 * 構文木（kxc.h の struct kxe / kxs / kxdef）を作る。字句は kxlex.c（lex.py と同じ切り方）が渡す。
 * Mac の上で bison 3.8 にかけて kxc.tab.c を作り、それを Xinu に入れる（install.sh）。
 */
%{
#include <xinu.h>
#include "kxc.h"
#define YYMALLOC(n)	kx_alloc(n)
#define YYFREE(p)	((void)(p))
#define YYSTACK_USE_ALLOCA 0
#define YYMAXDEPTH	2000
int	kxlex(void);
void	kxerror(const char *);
%}

%define api.prefix {kx}
%locations
%union { const char *s; struct kxe *e; struct kxl *l; struct kxs *st; struct kxitem *it; struct kxdef *d; struct kxname *n; int32 i; }

%token <s> NAME NUMBER STRING
%token K_DEFACTOR "というアクターを定義する。" K_HAS "を持つ。" K_INIT "の初期値は" K_TOSHI "とし、" K_TOSURU "とする。"
%token T_MSG "というメッセージ" K_RECV "を受け取ったとき、" KORE "これで" K_ENDDEF "の定義を終わる。"
%token K_RUN "実行を始める。" K_ENDRUN "実行を終わる。"
%token MARU "。" TEN "、" SONOATO "その後、" NARABA "ならば、" DENAKEREBA "でなければ、" YORICHIISA "より小さければ、"
%token SOUDENAKEREBA "そうでなければ、" K_BLOCK "次のことを行う。" IJOU "以上。" KARA "から" MADE_NITSUITE "までの各番号について、"
%token WA "は" TO "と" GA "が" NI "に" WO "を" NO "の" NO_MATSUBI "の末尾" NO_SENTOU_KARA "の先頭から" NO_ZENIN "の全員"
%token BANME "番目" SOREZORE "それぞれ" T_MOJIRETSU "という文字列" T_ACTOR "というアクター" ICHITSU "1つ"
%token HYOUJI_S "表示する" HYOUJI_R "表示し" OKURU_S "送る" OKURU_R "送り" HENKOU_S "変更する" HENKOU_R "変更し"
%token KUWAE_S "加える" KUWAE_R "加え" KUWAETA "加えた数"
%token TSUIKA_S "追加する" TSUIKA_R "追加し" TORIDASU_S "取り出す" TORIDASU_R "取り出し"
%token NAZUKE_S "名付ける" NAZUKE_R "名付け" SEISEI_R "生成し" YOUI_R "用意し"
%token HIITA "引いた数" WARIAMARI "で割った余り" NO_YOUSOSU "の要素数"
%token HAI "はい" IIE "いいえ" NASHI "なし" SORA "空" SORA_HAIRETSU "空の配列" JIBUN "自分" JIBUN_JISHIN "自分自身"
%token GENZAI "現在の番号" SONO "その" LP "（" RP "）"

%type <d> defs def
%type <n> names decl
%type <it> items item init inits initp
%type <st> stmts stmt body ifstmt part loop clause_s clause_r disp send chg add push take bind
%type <e> expr term idx arith maker sendarg cond
%type <l> exprs
%type <s> header

%define parse.error verbose
%start program

%%

/* ───── プログラム全体 ───── */
program : defs K_RUN stmts KORE K_ENDRUN
            { kx_prog.defs = $1; kx_prog.main = $3; kx_prog.mline = @2.first_line; kx_prog.mend = @5.first_line; }
        ;
defs    : %empty            { $$ = NULL; }
        | defs def          { $$ = kx_defappend($1, $2); }
        ;

/* ───── アクター定義 ───── */
def     : NAME K_DEFACTOR decl items KORE NAME K_ENDDEF
            { $$ = kx_def($1, $3, $4, $6, @1.first_line, @7.first_line); if (!$$) YYABORT; }
        ;
decl    : NAME WA names K_HAS   { $$ = $3; }
        ;
names   : NAME                  { $$ = kx_name($1, NULL); }
        | names TO NAME         { $$ = kx_name($3, $1); }
        ;
items   : %empty                { $$ = NULL; }
        | items item            { $$ = kx_itemappend($1, $2); }
        ;
item    : init                  { $$ = $1; }
        | header stmt           { $$ = kx_item(1, $1, $2, @1.first_line, @2.last_line); }
        | stmt                  { $$ = kx_item(2, NULL, $1, @1.first_line, @1.last_line); }
        ;
init    : inits K_TOSURU        { $$ = $1; }
        ;
inits   : initp                 { $$ = $1; }
        | inits K_TOSHI initp   { $$ = kx_itemappend($1, $3); }
        ;
initp   : exprs K_INIT expr     { $$ = kx_inits($1, $3, @1.first_line); if (!$$) YYABORT; }
        ;
/* 受信節の頭: 受け取る名前があれば「…と名前」。header は「メッセージ名\x1f受け取る名前」を返す */
header  : expr GA STRING T_MSG K_RECV              { $$ = kx_header($3, NULL); }
        | expr GA STRING T_MSG TO NAME K_RECV      { $$ = kx_header($3, $6); }
        ;

/* ───── 文 ───── */
stmts   : %empty                { $$ = NULL; }
        | stmts stmt            { $$ = kx_stappend($1, $2); }
        ;
stmt    : body MARU             { $$ = $1; }
        | SONOATO body MARU     { $$ = $2; }
        | ifstmt                { $$ = $1; }
        | SONOATO ifstmt        { $$ = $2; }
        | loop                  { $$ = $1; }
        ;
body    : clause_s              { $$ = $1; }
        | clause_r TEN body     { $$ = kx_stappend($1, $3); }
        ;
ifstmt  : cond part                         { $$ = kx_if($1, $2, NULL, @1.first_line); }
        | cond part SOUDENAKEREBA part      { $$ = kx_if($1, $2, $4, @1.first_line); }
        ;
part    : body MARU                 { $$ = $1; }
        | K_BLOCK stmts IJOU        { $$ = $2; }
        ;
/* 条件は比べ方を E_EQ / E_NE / E_LT の式にして持つ */
cond    : expr GA expr NARABA       { $$ = kx_e2(E_EQ, $1, $3, NULL); }
        | expr GA expr DENAKEREBA   { $$ = kx_e2(E_NE, $1, $3, NULL); }
        | expr GA expr YORICHIISA   { $$ = kx_e2(E_LT, $1, $3, NULL); }
        ;
loop    : expr KARA expr MADE_NITSUITE part   { $$ = kx_loop($1, $3, $5, @1.first_line); }
        ;

/* ───── 節 ───── */
clause_s: disp HYOUJI_S   { $$ = $1; } | send OKURU_S    { $$ = $1; } | chg HENKOU_S { $$ = $1; }
        | add  KUWAE_S    { $$ = $1; } | push TSUIKA_S   { $$ = $1; } | take TORIDASU_S { $$ = $1; }
        | bind NAZUKE_S   { $$ = $1; }
        ;
clause_r: disp HYOUJI_R   { $$ = $1; } | send OKURU_R    { $$ = $1; } | chg HENKOU_R { $$ = $1; }
        | add  KUWAE_R    { $$ = $1; } | push TSUIKA_R   { $$ = $1; } | take TORIDASU_R { $$ = $1; }
        | bind NAZUKE_R   { $$ = $1; }
        ;
disp    : exprs WO                                   { $$ = kx_st(S_DISP, $1, NULL, NULL, NULL, @1.first_line); }
        ;
send    : exprs NI STRING T_MSG sendarg WO           { $$ = kx_st(S_SEND, $1, $5, NULL, $3, @1.first_line); }
        | exprs NI SOREZORE STRING T_MSG sendarg WO  { $$ = kx_st(S_SEND, $1, $6, NULL, $4, @1.first_line); }
        | expr NO_ZENIN NI STRING T_MSG sendarg WO   { $$ = kx_st(S_ZENIN, NULL, $1, $6, $4, @1.first_line); }
        ;
sendarg : %empty                { $$ = NULL; }
        | TO expr               { $$ = $2; }
        ;
chg     : exprs WO expr NI                           { $$ = kx_st(S_CHG, $1, $3, NULL, NULL, @1.first_line); }
        ;
add     : exprs NI expr WO                           { $$ = kx_st(S_ADD, $1, $3, NULL, NULL, @1.first_line); }
        ;
push    : exprs WO expr NI                           { $$ = kx_st(S_PUSH, $1, $3, NULL, NULL, @1.first_line); }
        | exprs WO expr NO_MATSUBI NI                { $$ = kx_st(S_PUSH, $1, $3, NULL, NULL, @1.first_line); }
        ;
take    : expr NO_SENTOU_KARA NAME WO                { $$ = kx_st(S_TAKE, NULL, kx_e(E_NAME, $3), $1, NULL, @1.first_line); }
        ;
bind    : maker TEN NAME TO                          { $$ = kx_bind($1, $3, @1.first_line); }
        ;
maker   : NAME T_ACTOR WO ICHITSU SEISEI_R           { $$ = kx_e(E_NEW, $1); }
        | exprs WO YOUI_R                            { $$ = $1->e; }
        ;

/* ───── 式 ───── */
exprs   : expr                  { $$ = kx_list($1, NULL); }
        | exprs TO expr         { $$ = kx_list($3, $1); }
        ;
expr    : term                  { $$ = $1; }
        ;
term    : NAME                  { $$ = kx_e(E_NAME, $1); }
        | SONO NAME             { $$ = kx_e(E_NAME, $2); }
        | NUMBER                { $$ = kx_e(E_NUM, $1); }
        | STRING                { $$ = kx_e(E_STR, $1); }
        | STRING T_MOJIRETSU    { $$ = kx_e(E_STR, $1); }
        | HAI                   { $$ = kx_e(E_TRUE, "はい"); }
        | IIE                   { $$ = kx_e(E_FALSE, "いいえ"); }
        | NASHI                 { $$ = kx_e(E_NONE, "なし"); }
        | SORA                  { $$ = kx_e(E_ARR, "空"); }
        | SORA_HAIRETSU         { $$ = kx_e(E_ARR, "空の配列"); }
        | JIBUN                 { $$ = kx_e(E_SELF, "自分"); }
        | JIBUN_JISHIN          { $$ = kx_e(E_SELF, "自分"); }
        | GENZAI                { $$ = kx_e(E_CUR, "現在の番号"); }
        | term NO NAME          { $$ = kx_e2(E_FIELD, $1, kx_e(E_NAME, $3), "の"); }
        | term NO idx BANME     { $$ = kx_e2(E_INDEX, $1, $3, "番目"); }
        | term NO_YOUSOSU       { $$ = kx_e2(E_LEN, $1, NULL, "の要素数"); }
        | arith                 { $$ = $1; }
        ;
arith   : LP expr NI expr WO KUWAETA RP     { $$ = kx_e2(E_ADD, $2, $4, "足す"); }
        | LP expr KARA expr WO HIITA RP     { $$ = kx_e2(E_SUB, $2, $4, "引く"); }
        | LP expr WO expr WARIAMARI RP      { $$ = kx_e2(E_MOD, $2, $4, "で割った余り"); }
        ;
idx     : NUMBER                { $$ = kx_e(E_NUM, $1); }
        | GENZAI                { $$ = kx_e(E_CUR, "現在の番号"); }
        | LP expr RP            { $$ = $2; }
        | arith                 { $$ = $1; }
        ;
%%
