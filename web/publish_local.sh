#!/bin/sh
# ~/kotonoha の文法・変換器から、公開用フォルダ kodamay.org/kotonoha/ を組み立てる
set -e
cd "$(dirname "$0")"
OUT=~/kodamay_org_site/kodamay.org/kotonoha
mkdir -p "$OUT"
./build.sh >/dev/null
python3 - "$OUT" <<'PY'
import sys, json, html
out = sys.argv[1]
src = open("site/index.src.html", encoding="utf-8").read()
bnf = open("../文法_BNF.txt", encoding="utf-8").read().rstrip()
open(f"{out}/index.html", "w", encoding="utf-8").write(src.replace("@@BNF@@", html.escape(bnf, quote=False)))
samples = [
  ("5人の哲学者（フォークをアクターとする版）", "../哲学者_文章形式.txt", False),
  ("5人の哲学者（デッドロックする版：全員が左から取る）", "../tests/哲学者_デッドロック版.txt", False),
  ("例題：ユークリッドの互除法（最大公約数）", "../例題/ユークリッドの互除法.txt", False),
  ("例題：ハノイの塔（4枚・返事を待つ再帰）", "../例題/ハノイの塔.txt", False),
  ("例題：バブルソート", "../例題/バブルソート.txt", False),
  ("例題：クイックソート（左右を別のアクターが並列に）", "../例題/クイックソート.txt", False),
  ("あいさつ（いちばん小さなプログラム）", "../tests/あいさつ.txt", False),
  ("書き方をひと通り（入れ子・繰り返し・送信）", "../tests/書き方の網羅.txt", False),
  ("「その後、」はどこに属するか", "../tests/その後の位置.txt", False),
  ("文法違反の例：条件を直接入れ子にする", "../tests/入れ子の条件.txt", True),
]
arr = [{"title": t, "text": open(p, encoding="utf-8").read(), "expectError": e} for t, p, e in samples]
open(f"{out}/samples.js", "w", encoding="utf-8").write("var KOTONOHA_SAMPLES = " + json.dumps(arr, ensure_ascii=False, indent=1) + ";\n")
PY
cp kotonoha.js site/app.js site/flow.html site/flow.js "$OUT/"
for f in "$OUT"/*.js; do node --check "$f"; done
chmod 644 "$OUT"/*
ls -la "$OUT"
