#!/bin/sh
# kotonoha.y → kotonoha.jison → kotonoha_parser.js → kotonoha.js（runtime.js に埋め込む）
set -e
cd "$(dirname "$0")"
python3 y2jison.py ../kotonoha.y > kotonoha.jison
npx jison kotonoha.jison -m js -p lr -o kotonoha_parser.js
python3 - <<'PY'
r = open("runtime.js", encoding="utf-8").read()
p = open("kotonoha_parser.js", encoding="utf-8").read()
open("kotonoha.js", "w", encoding="utf-8").write(r.replace("/*@@PARSER@@*/", p))
PY
node --check kotonoha.js
echo built kotonoha.js
