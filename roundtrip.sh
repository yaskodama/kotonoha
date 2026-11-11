#!/bin/sh
# 往復検査: 文章 →(kotonoha) 構造 S1 →(to_bunsho) 文章' →(kotonoha) 構造 S2 →(to_bunsho) 文章''
#   合格条件: S1 = S2（構造は往復で一字も変わらない）かつ 文章' = 文章''（標準形は変換しても変わらない）
# 使い方: ./roundtrip.sh [-p] 文章形式.txt   （-p で許容版の解析器を使う）
P=./kotonoha; [ "$1" = -p ] && { P=./許容版/kotonoha; shift; }
D=$(mktemp -d); f="$1"
python3 lex.py "$f" | $P > $D/S1 || { echo "NG 元の文章が解析できない: $f"; exit 1; }
python3 to_bunsho.py $D/S1 > $D/B2 || { echo "NG 逆変換に失敗: $f"; exit 1; }
python3 lex.py $D/B2 | $P > $D/S2 || { echo "NG 逆変換した文章が解析できない: $f"; cat -n $D/B2; exit 1; }
python3 to_bunsho.py $D/S2 > $D/B3
cmp -s $D/S1 $D/S2 && s=OK || s=NG; cmp -s $D/B2 $D/B3 && b=OK || b=NG
echo "$f  構造の往復:$s  文章の不動点:$b"
[ -n "$KEEP" ] && cp $D/S1 "$KEEP.構造" && cp $D/B2 "$KEEP.文章"
[ $s = OK ] && [ $b = OK ]
