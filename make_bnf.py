#!/usr/bin/env python3
"""bison の報告書(kotonoha.report)の Grammar 節から、終端記号を日本語の言葉に戻した BNF を作る。"""
import re, sys
sys.path.insert(0, ".")
from lex import KW
rev = {}
for k, v in KW.items():
    rev.setdefault(v, []).append(k)
rev.update({"NAME": ["名前"], "NUMBER": ["数"], "STRING": ["「文字列」"]})
JP = {"program":"プログラム","defs":"定義の並び","def":"アクター定義","decl":"状態宣言","names":"名前の並び",
 "items":"定義本体","item":"定義の項目","init":"初期値文","inits":"初期値の並び","initp":"初期値",
 "header":"受信の頭","stmts":"文の並び","stmt":"文","body":"一文の中身","ifstmt":"条件文","part":"本体",
 "cond":"条件","loop":"繰り返し文","clause_s":"終止節","clause_r":"連用節","disp":"表示の前半","send":"送信の前半",
 "sendarg":"添え物","chg":"変更の前半","add":"加算の前半","push":"追加の前半","take":"取り出しの前半",
 "bind":"名付けの前半","maker":"作るもの","exprs":"式の並び","expr":"式","term":"項","idx":"位置","arith":"計算"}
g = open("kotonoha.report", encoding="utf-8").read().split("Grammar")[1].split("Terminals")[0]
out, lhs = [], None
for line in g.splitlines():
    m = re.match(r"\s*(\d+) (?:(\w+):|\s*\|)\s*(.*)", line)
    if not m or m.group(2) == "$accept": continue
    if m.group(2): lhs = m.group(2)
    rhs = []
    for s in m.group(3).split():
        if s == "ε": rhs.append("ε")
        elif s in JP: rhs.append(f"<{JP[s]}>")
        else: rhs.append('"' + "|".join(rev[s]) + '"')
    head = f"<{JP[lhs]}>" if m.group(2) else ""
    out.append(f"{m.group(1):>3} {head:<14}{'::=' if m.group(2) else '  |'} {' '.join(rhs)}")
print("\n".join(out))
