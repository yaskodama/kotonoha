#!/usr/bin/env python3
"""kotonoha.y（bison）→ kotonoha.jison。規則と動作はそのまま写す（動作の中身は C と JS で同じ式になるように書いてある）。"""
import re, sys
s = open(sys.argv[1], encoding="utf-8").read()
rules = s.split("\n%%\n")[1]
rules = re.sub(r"/\*.*?\*/", "", rules, flags=re.S)        # 注釈を除く
rules = rules.replace("%empty", "")
toks = re.findall(r"^%token(?:\s+<\w+>)?\s+(.+)$", s, re.M)
toks = " ".join(t.strip() for t in toks)
print("%start program\n%token " + toks + "\n%%\n" + rules.strip() + "\n")
