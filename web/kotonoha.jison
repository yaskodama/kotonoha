%start program
%token NAME NUMBER STRING K_DEFACTOR K_HAS K_INIT K_TOSHI K_TOSURU T_MSG K_RECV KORE K_ENDDEF K_RUN K_ENDRUN MARU TEN SONOATO NARABA DENAKEREBA YORICHIISA SOUDENAKEREBA K_BLOCK IJOU KARA MADE_NITSUITE WA TO GA NI WO NO NO_MATSUBI NO_SENTOU_KARA NO_ZENIN BANME SOREZORE T_MOJIRETSU T_ACTOR ICHITSU HYOUJI_S HYOUJI_R OKURU_S OKURU_R HENKOU_S HENKOU_R KUWAE_S KUWAE_R KUWAETA TSUIKA_S TSUIKA_R TORIDASU_S TORIDASU_R NAZUKE_S NAZUKE_R SEISEI_R YOUI_R HIITA WARIAMARI NO_YOUSOSU HAI IIE NASHI SORA SORA_HAIRETSU JIBUN JIBUN_JISHIN GENZAI SONO LP RP
%%
program : defs K_RUN stmts KORE K_ENDRUN
            { output = cat(4, $1, "実行を始める。\n", ind($3), "実行を終わる。\n"); }
        ;
defs    :             { $$ = ""; }
        | defs def          { $$ = cat(3, $1, $2, "\n"); }
        ;



def     : NAME K_DEFACTOR decl items KORE NAME K_ENDDEF
            { $$ = print_def($1, $3, $4, $6); }
        ;

decl    : NAME WA names K_HAS   { $$ = $3; }
        ;
names   : NAME                  { $$ = $1; }
        | names TO NAME         { $$ = cat(3, $1, SEP, $3); }
        ;

items   :                 { $$ = NULL; }
        | items item            { $$ = append($1, $2); }
        ;
item    : init                  { $$ = mkitem(0, NULL, NULL, $1); }
        | header stmt           { $$ = mkitem(1, NULL, $1, $2); }
        | stmt                  { $$ = mkitem(2, NULL, NULL, $1); }
        ;

init    : inits K_TOSURU        { $$ = $1; }
        ;
inits   : initp                 { $$ = $1; }
        | inits K_TOSHI initp   { $$ = cat(2, $1, $3); }
        ;
initp   : exprs K_INIT expr
            { $$ = initlines($1, $3); }   
        ;

header  : expr GA STRING T_MSG K_RECV              { $$ = cat(2, $3, "を受け取ったとき、"); }
        | expr GA STRING T_MSG TO NAME K_RECV      { $$ = cat(4, $3, "と ", $6, " を受け取ったとき、"); }
        ;


stmts   :                 { $$ = ""; }
        | stmts stmt            { $$ = cat(2, $1, $2); }
        ;
stmt    : body MARU             { $$ = $1; }
        | SONOATO body MARU     { $$ = $2; }
        | ifstmt                { $$ = $1; }
        | SONOATO ifstmt        { $$ = $2; }
        | loop                  { $$ = $1; }
        ;

body    : clause_s              { $$ = cat(2, $1, "。\n"); }
        | clause_r TEN body     { $$ = cat(3, $1, "。\n", $3); }
        ;


ifstmt  : cond part                         { $$ = cat(4, $1, "\n", ind($2), "以上。\n"); }
        | cond part SOUDENAKEREBA part      { $$ = cat(6, $1, "\n", ind($2), "そうでなければ、\n", ind($4), "以上。\n"); }
        ;
part    : body MARU                 { $$ = $1; }
        | K_BLOCK stmts IJOU        { $$ = $2; }
        ;
cond    : expr GA expr NARABA       { $$ = cat(5, "もし ", $1, " が ", $3, " ならば、"); }
        | expr GA expr DENAKEREBA   { $$ = cat(5, "もし ", $1, " が ", $3, " でない ならば、"); }
        | expr GA expr YORICHIISA   { $$ = cat(5, "もし ", $1, " が ", $3, " より小さい ならば、"); }
        ;

loop    : expr KARA expr MADE_NITSUITE part
            { $$ = cat(6, bnd($1), "から", bnd($3), "まで繰り返す。\n", ind($5), "以上。\n"); }
        ;


clause_s: disp HYOUJI_S   { $$ = $1; } | send OKURU_S    { $$ = $1; } | chg HENKOU_S { $$ = $1; }
        | add  KUWAE_S    { $$ = $1; } | push TSUIKA_S   { $$ = $1; } | take TORIDASU_S { $$ = $1; }
        | bind NAZUKE_S   { $$ = $1; }
        ;
clause_r: disp HYOUJI_R   { $$ = $1; } | send OKURU_R    { $$ = $1; } | chg HENKOU_R { $$ = $1; }
        | add  KUWAE_R    { $$ = $1; } | push TSUIKA_R   { $$ = $1; } | take TORIDASU_R { $$ = $1; }
        | bind NAZUKE_R   { $$ = $1; }
        ;

disp    : exprs WO                                   { $$ = cat(2, join($1, " と "), " を表示する"); }
        ;

send    : exprs NI STRING T_MSG sendarg WO           { $$ = cat(5, join($1, " と "), " に", $3, $5, "を送る"); }
        | exprs NI SOREZORE STRING T_MSG sendarg WO  { $$ = cat(5, join($1, " と "), " に それぞれ", $4, $6, "を送る"); }
        | expr NO_ZENIN NI STRING T_MSG sendarg WO   { $$ = cat(5, $1, " の全員に", $4, $6, "を送る"); }
        ;
sendarg :                 { $$ = ""; }
        | TO expr               { $$ = cat(3, "と ", $2, " "); }
        ;

chg     : exprs WO expr NI                           { $$ = cat(3, join($1, " と "), " は ", $3); }
        ;

add     : exprs NI expr WO                           { $$ = cat(5, $1, " は ", $1, " 足す ", $3); }
        ;

push    : exprs WO expr NI                           { $$ = cat(4, $3, " に ", join($1, " と "), " を追加する"); }
        | exprs WO expr NO_MATSUBI NI                { $$ = cat(4, $3, " に ", join($1, " と "), " を追加する"); }
        ;

take    : expr NO_SENTOU_KARA NAME WO                { $$ = cat(4, $3, " は ", $1, " の先頭を取り出す"); }
        ;

bind    : maker TEN NAME TO                          { $$ = cat(3, $3, " は ", $1); }
        ;
maker   : NAME T_ACTOR WO ICHITSU SEISEI_R           { $$ = cat(3, "「", $1, "」の新しいアクター"); }
        | exprs WO YOUI_R                            { $$ = $1; }
        ;


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

arith   : LP expr NI expr WO KUWAETA RP     { $$ = cat(5, "（", $2, " 足す ", $4, "）"); }
        | LP expr KARA expr WO HIITA RP     { $$ = cat(5, "（", $2, " 引く ", $4, "）"); }
        | LP expr WO expr WARIAMARI RP      { $$ = cat(5, "（", $2, " を ", $4, " で割った余り）"); }
        ;
idx     : NUMBER                { $$ = $1; }
        | GENZAI                { $$ = "現在の番号"; }
        | LP expr RP            { $$ = $2; }
        | arith                 { $$ = $1; }
        ;

