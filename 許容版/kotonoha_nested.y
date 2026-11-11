/* ことのは 文章形式（インデントなし）の文法  ── 一文方式・厳格版
 *
 * 決まり:
 *   - 文は「。」で終わる。一つの文の中では動作を「、」でつなぐ（連用形「〜し、」で続け、終止形「〜する。」で閉じる）。
 *   - 「〜ならば、」「そうでなければ、」「〜について、」の本体は**その一文だけ**。
 *     二文以上を入れるときは「次のことを行う。 … 以上。」で囲む。
 *   - 厳格版では、一文の本体に条件文を直接は書けない（入れ子は「次のことを行う。」の中に書く）。
 *   - 受信節（「〜を受け取ったとき、」）の本体は、次の受信節か「これで〜の定義を終わる。」まで。
 *
 * 解析しながら構文木を作らず、そのまま構造化形式（インデントあり）の文字列を組み立てて出力する。
 */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
int yylex(void);
void yyerror(const char *);
char *cat(int n, ...);
char *ind(const char *);
char *join(const char *, const char *);
char *initlines(char *, char *);
char *bnd(char *);
typedef struct Item { int kind; char *actor, *h, *s; struct Item *next; } Item;
Item *mkitem(int kind, char *actor, char *h, char *s);
Item *append(Item *a, Item *b);
char *print_def(char *name, char *decl, Item *items, char *endname);
extern int curline; extern char curtext[];
static char *output;
#define SEP "\x1f"   /* 並び（〜と〜と〜）の区切り */
%}

%union { char *s; struct Item *it; }

%token <s> NAME NUMBER STRING
%token K_DEFACTOR K_HAS K_INIT K_TOSHI K_TOSURU T_MSG K_RECV KORE K_ENDDEF K_RUN K_ENDRUN
%token MARU TEN SONOATO NARABA DENAKEREBA YORICHIISA SOUDENAKEREBA K_BLOCK IJOU KARA MADE_NITSUITE
%token WA TO GA NI WO NO NO_MATSUBI NO_SENTOU_KARA NO_ZENIN BANME SOREZORE T_MOJIRETSU T_ACTOR ICHITSU
%token HYOUJI_S HYOUJI_R OKURU_S OKURU_R HENKOU_S HENKOU_R KUWAE_S KUWAE_R KUWAETA
%token TSUIKA_S TSUIKA_R TORIDASU_S TORIDASU_R NAZUKE_S NAZUKE_R SEISEI_R YOUI_R
%token HIITA WARIAMARI NO_YOUSOSU
%token HAI IIE NASHI SORA SORA_HAIRETSU JIBUN JIBUN_JISHIN GENZAI SONO LP RP

%type <s> program defs def decl names init inits initp header stmts stmt body ifstmt part cond loop
%type <s> clause_s clause_r disp send sendarg chg add push take bind maker expr exprs term idx arith
%type <it> items item

%define parse.error verbose
%expect 1   /* そうでなければ の付き先: シフト優先＝一番近い「ならば」に付く */
%start program

%%

/* ───── プログラム全体 ───── */
program : defs K_RUN stmts KORE K_ENDRUN
            { output = cat(4, $1, "実行を始める。\n", ind($3), "実行を終わる。\n"); }
        ;
defs    : %empty            { $$ = ""; }
        | defs def          { $$ = cat(3, $1, $2, "\n"); }
        ;

/* ───── アクター定義 ───── */
/* 例: フォークというアクターを定義する。 … これでフォークの定義を終わる。 */
def     : NAME K_DEFACTOR decl items KORE NAME K_ENDDEF
            { $$ = print_def($1, $3, $4, $6); }
        ;
/* 例: フォークは番号と使用中と待ち行列を持つ。 */
decl    : NAME WA names K_HAS   { $$ = $3; }
        ;
names   : NAME                  { $$ = $1; }
        | names TO NAME         { $$ = cat(3, $1, SEP, $3); }
        ;
/* 定義の中身は「初期値の文」「受信節の頭＋一文」「文」の平らな並び。
 * どれがどこに属するかは print_def が意味の段階で振り分ける（文法を平らにすると LR(1) の衝突が消える）。 */
items   : %empty                { $$ = NULL; }
        | items item            { $$ = append($1, $2); }
        ;
item    : init                  { $$ = mkitem(0, NULL, NULL, $1); }
        | header stmt           { $$ = mkitem(1, NULL, $1, $2); }
        | stmt                  { $$ = mkitem(2, NULL, NULL, $1); }
        ;
/* 例: 番号の初期値は0とし、使用中の初期値はいいえとし、待ち行列の初期値は空とする。 */
init    : inits K_TOSURU        { $$ = $1; }
        ;
inits   : initp                 { $$ = $1; }
        | inits K_TOSHI initp   { $$ = cat(2, $1, $3); }
        ;
initp   : exprs K_INIT expr
            { $$ = initlines($1, $3); }   /* 「AとBの初期値はv」→ A は v。 B は v。 */
        ;
/* 例: 哲学者が「開始」というメッセージを受け取ったとき、
 *     フォークが「取りたい」というメッセージと哲学者を受け取ったとき、 */
header  : expr GA STRING T_MSG K_RECV              { $$ = cat(2, $3, "を受け取ったとき、"); }
        | expr GA STRING T_MSG TO NAME K_RECV      { $$ = cat(4, $3, "と ", $6, " を受け取ったとき、"); }
        ;

/* ───── 文 ───── */
stmts   : %empty                { $$ = ""; }
        | stmts stmt            { $$ = cat(2, $1, $2); }
        ;
stmt    : body MARU             { $$ = $1; }
        | SONOATO body MARU     { $$ = $2; }
        | ifstmt                { $$ = $1; }
        | SONOATO ifstmt        { $$ = $2; }
        | loop                  { $$ = $1; }
        ;
/* 一つの文 = 連用節「、」…「、」終止節 */
body    : clause_s              { $$ = cat(2, $1, "。\n"); }
        | clause_r TEN body     { $$ = cat(3, $1, "。\n", $3); }
        ;

/* 条件文。本体は一文、または「次のことを行う。…以上。」 */
ifstmt  : cond part                         { $$ = cat(4, $1, "\n", ind($2), "以上。\n"); }
        | cond part SOUDENAKEREBA part      { $$ = cat(6, $1, "\n", ind($2), "そうでなければ、\n", ind($4), "以上。\n"); }
        ;
part    : body MARU                 { $$ = $1; }
        | K_BLOCK stmts IJOU        { $$ = $2; }
        | ifstmt                    { $$ = $1; }
        ;
cond    : expr GA expr NARABA       { $$ = cat(5, "もし ", $1, " が ", $3, " ならば、"); }
        | expr GA expr DENAKEREBA   { $$ = cat(5, "もし ", $1, " が ", $3, " でない ならば、"); }
        | expr GA expr YORICHIISA   { $$ = cat(5, "もし ", $1, " が ", $3, " より小さい ならば、"); }
        ;
/* 例: 1から5までの各番号について、… ／ 1から列の要素数までの各番号について、…
 * 範囲は式。範囲の式は繰り返しに入る前に一度だけ計算する（入れ子なら外側の「現在の番号」が見える）。 */
loop    : expr KARA expr MADE_NITSUITE part
            { $$ = cat(6, bnd($1), "から", bnd($3), "まで繰り返す。\n", ind($5), "以上。\n"); }
        ;

/* ───── 節（終止形 _S と連用形 _R で同じ形） ───── */
clause_s: disp HYOUJI_S   { $$ = $1; } | send OKURU_S    { $$ = $1; } | chg HENKOU_S { $$ = $1; }
        | add  KUWAE_S    { $$ = $1; } | push TSUIKA_S   { $$ = $1; } | take TORIDASU_S { $$ = $1; }
        | bind NAZUKE_S   { $$ = $1; }
        ;
clause_r: disp HYOUJI_R   { $$ = $1; } | send OKURU_R    { $$ = $1; } | chg HENKOU_R { $$ = $1; }
        | add  KUWAE_R    { $$ = $1; } | push TSUIKA_R   { $$ = $1; } | take TORIDASU_R { $$ = $1; }
        | bind NAZUKE_R   { $$ = $1; }
        ;
/* AとBを表示する */
disp    : exprs WO                                   { $$ = cat(2, join($1, " と "), " を表示する"); }
        ;
/* Xに「m」というメッセージ[とY]を送る ／ AとBにそれぞれ「m」… ／ Xの全員に「m」… */
send    : exprs NI STRING T_MSG sendarg WO           { $$ = cat(5, join($1, " と "), " に", $3, $5, "を送る"); }
        | exprs NI SOREZORE STRING T_MSG sendarg WO  { $$ = cat(5, join($1, " と "), " に それぞれ", $4, $6, "を送る"); }
        | expr NO_ZENIN NI STRING T_MSG sendarg WO   { $$ = cat(5, $1, " の全員に", $4, $6, "を送る"); }
        ;
sendarg : %empty                { $$ = ""; }
        | TO expr               { $$ = cat(3, "と ", $2, " "); }
        ;
/* XをYに変更する（設定する） */
chg     : exprs WO expr NI                           { $$ = cat(3, join($1, " と "), " は ", $3); }
        ;
/* XにYを加える */
add     : exprs NI expr WO                           { $$ = cat(5, $1, " は ", $1, " 足す ", $3); }
        ;
/* XをYに追加する ／ XをYの末尾に追加する */
push    : exprs WO expr NI                           { $$ = cat(4, $3, " に ", join($1, " と "), " を追加する"); }
        | exprs WO expr NO_MATSUBI NI                { $$ = cat(4, $3, " に ", join($1, " と "), " を追加する"); }
        ;
/* Xの先頭からNを取り出す */
take    : expr NO_SENTOU_KARA NAME WO                { $$ = cat(4, $3, " は ", $1, " の先頭を取り出す"); }
        ;
/* Aというアクターを1つ生成し、Nと名付ける ／ 空の配列を用意し、Nと名付ける */
bind    : maker TEN NAME TO                          { $$ = cat(3, $3, " は ", $1); }
        ;
maker   : NAME T_ACTOR WO ICHITSU SEISEI_R           { $$ = cat(3, "「", $1, "」の新しいアクター"); }
        | exprs WO YOUI_R                            { $$ = $1; }
        ;

/* ───── 式 ───── */
exprs   : expr                  { $$ = $1; }
        | exprs TO expr         { $$ = cat(3, $1, SEP, $3); }
        ;
expr    : term                  { $$ = $1; }
        ;
term    : NAME                  { $$ = $1; }
        | SONO NAME             { $$ = $2; }
        | NUMBER                { $$ = $1; }
        | STRING                { $$ = $1; }
        | STRING T_MOJIRETSU    { $$ = $1; }
        | HAI                   { $$ = "はい"; }
        | IIE                   { $$ = "いいえ"; }
        | NASHI                 { $$ = "なし"; }
        | SORA                  { $$ = "空"; }
        | SORA_HAIRETSU         { $$ = "空の配列"; }
        | JIBUN                 { $$ = "自分"; }
        | JIBUN_JISHIN          { $$ = "自分"; }
        | GENZAI                { $$ = "現在の番号"; }
        | term NO NAME          { $$ = cat(3, $1, "の", $3); }
        | term NO idx BANME     { $$ = cat(4, $1, "の ", $3, " 番目"); }
        | term NO_YOUSOSU       { $$ = cat(2, $1, " の要素数"); }
        | arith                 { $$ = $1; }
        ;
/* 計算は括弧で囲む: （AにBを加えた数） （AからBを引いた数） （AをBで割った余り） */
arith   : LP expr NI expr WO KUWAETA RP     { $$ = cat(5, "（", $2, " 足す ", $4, "）"); }
        | LP expr KARA expr WO HIITA RP     { $$ = cat(5, "（", $2, " 引く ", $4, "）"); }
        | LP expr WO expr WARIAMARI RP      { $$ = cat(5, "（", $2, " を ", $4, " で割った余り）"); }
        ;
idx     : NUMBER                { $$ = $1; }
        | GENZAI                { $$ = "現在の番号"; }
        | LP expr RP            { $$ = $2; }
        | arith                 { $$ = $1; }
        ;
%%

int curline; char curtext[4096];

int yylex(void) {
    int code; char buf[4096];
    if (!fgets(buf, sizeof buf, stdin)) return 0;
    buf[strcspn(buf, "\n")] = 0;
    char *p = strchr(buf, '\t'), *q = p ? strchr(p + 1, '\t') : NULL;
    code = atoi(buf); curline = p ? atoi(p + 1) : 0;
    strcpy(curtext, q ? q + 1 : "");
    yylval.s = strdup(curtext);
    return code;
}
void yyerror(const char *m) {
    fprintf(stderr, "構文エラー %d行 「%s」の所: %s\n", curline, curtext, m);
}
char *cat(int n, ...) {
    va_list ap; size_t len = 1; int i;
    va_start(ap, n); for (i = 0; i < n; i++) len += strlen(va_arg(ap, char *)); va_end(ap);
    char *r = malloc(len); r[0] = 0;
    va_start(ap, n); for (i = 0; i < n; i++) strcat(r, va_arg(ap, char *)); va_end(ap);
    return r;
}
char *ind(const char *s) {               /* 各行の頭に4字下げ */
    char *r = malloc(strlen(s) * 2 + 8), *w = r; int bol = 1;
    for (; *s; s++) { if (bol && *s != '\n') { memcpy(w, "    ", 4); w += 4; } *w++ = *s; bol = (*s == '\n'); }
    *w = 0; return r;
}
char *join(const char *s, const char *sep) {
    char *r = strdup(""), *p = strdup(s), *q; int first = 1;
    for (q = strtok(p, SEP); q; q = strtok(NULL, SEP)) { r = cat(3, r, first ? "" : sep, q); first = 0; }
    return r;
}
char *initlines(char *names, char *v) {
    char *r = "", *p = strdup(names), *q;
    for (q = strtok(p, SEP); q; q = strtok(NULL, SEP)) r = cat(5, r, q, " は ", v, "。\n");
    return r;
}
/* 繰り返しの範囲: 数ならそのまま、全体が（…）ならそのまま、それ以外は（…）で囲む（構造化形式で読みやすく） */
char *bnd(char *s) {
    const char *p = s; int d = 0;
    while (*p >= '0' && *p <= '9') p++;
    if (!*p && p != s) return s;
    if (strncmp(s, "（", 3)) return cat(3, "（", s, "）");
    for (p = s; *p; ) {
        if (!strncmp(p, "（", 3)) { d++; p += 3; }
        else if (!strncmp(p, "）", 3)) { d--; p += 3; if (!d) return *p ? cat(3, "（", s, "）") : s; }
        else p++;
    }
    return s;
}
Item *mkitem(int kind, char *actor, char *h, char *s) {
    Item *it = calloc(1, sizeof *it); it->kind = kind; it->actor = actor; it->h = h; it->s = s; return it;
}
Item *append(Item *a, Item *b) { Item *p = a; if (!a) return b; while (p->next) p = p->next; p->next = b; return a; }

/* 平らな並びを、初期状態と受信節ごとのかたまりに振り分けて字下げ出力する */
char *print_def(char *name, char *decl, Item *items, char *endname) {
    char *init = "", *body = "", *cur = NULL; Item *it;
    if (strcmp(name, endname)) { fprintf(stderr, "意味エラー: 「%s」の定義を「%s」で閉じている\n", name, endname); exit(1); }
    for (it = items; it; it = it->next) {
        if (it->kind == 0) { if (cur || *body) { fprintf(stderr, "意味エラー: %s の初期値の文は受信節より前に書く\n", name); exit(1); } init = cat(2, init, it->s); }
        else if (it->kind == 1) { if (cur) body = cat(4, body, cur, "以上。\n", ""); cur = cat(3, it->h, "\n", ind(it->s)); }
        else { if (!cur) { fprintf(stderr, "意味エラー: %s で受信節の外に文がある\n", name); exit(1); } cur = cat(2, cur, ind(it->s)); }
    }
    if (cur) body = cat(3, body, cur, "以上。\n");
    char *in = *init ? cat(3, "初期状態は\n", ind(init), "以上。\n") : "";
    return cat(7, "「", name, "」というアクターを定義する。\n",
               ind(cat(3, "状態は ", join(decl, "、"), "。\n")), ind(in), ind(body), "定義を終わる。\n");
}

int main(void) {
    if (yyparse()) return 1;
    fputs(output, stdout);
    return 0;
}
