#!/usr/bin/env python3
"""ことのは 構造化形式（インデントあり） → 文章形式（インデントなし） の変換器。

kotonoha（bison 解析器）が出す構造化形式を読み、kotonoha.y の厳格版の文法に通る文章形式を書き出す。
構造化形式はブロックを「以上。」「定義を終わる。」「実行を終わる。」で閉じるので、字下げに頼らず行単位で読める。

文章形式に戻すときの決まり（＝標準の書き方。元の言い回しは構文木に残っていないので戻らない）:
  - 単純な文（表示・送信・変更・加算・追加・取り出し・名付け）が続くところは、3つまでを「、」でつないで一文にする。
  - 条件・繰り返しの本体が単純な文3つ以内なら一文、それ以外は「次のことを行う。…以上。」で囲む（一文方式の厳格版に従う）。
  - 他のアクターの状態に代入する（「人の番号」のように「の」を含む）ときは「設定する」、それ以外は「変更する」。
  - 単独の「自分」は「自分自身」、表示する「「…」」には「という文字列」を付ける。
  - 初期値は、同じ値が続く名前を「AとBの初期値はv」にまとめる。

使い方: python3 to_bunsho.py 構造化形式.txt > 文章形式.txt
"""
import re, sys

# ───────────── 構造化形式を読んで木にする ─────────────

class Lines:
    def __init__(self, text):
        self.ls = [(i + 1, l.strip()) for i, l in enumerate(text.split("\n")) if l.strip()]
        self.i = 0
    def peek(self):  return self.ls[self.i][1] if self.i < len(self.ls) else None
    def next(self):
        n, l = self.ls[self.i]; self.i += 1; return n, l
    def expect(self, s):
        n, l = self.next()
        if l != s: sys.exit(f"{n}行: 「{s}」のはずが「{l}」")

def parse_program(L):
    defs = []
    while L.peek() and L.peek().endswith("というアクターを定義する。"):
        defs.append(parse_def(L))
    L.expect("実行を始める。")
    body = parse_block(L, ("実行を終わる。",))
    L.expect("実行を終わる。")
    return defs, body

def parse_def(L):
    n, l = L.next()
    name = re.fullmatch(r"「(.+?)」というアクターを定義する。", l).group(1)
    n, l = L.next()
    fields = re.fullmatch(r"状態は (.+)。", l).group(1).split("、")
    inits = []
    if L.peek() == "初期状態は":
        L.next()
        while L.peek() != "以上。":
            n, l = L.next()
            m = re.fullmatch(r"(\S+) は (.+)。", l)
            inits.append((m.group(1), m.group(2)))
        L.next()
    handlers = []
    while L.peek() != "定義を終わる。":
        n, l = L.next()
        m = re.fullmatch(r"「(.+?)」(?:と (\S+) )?を受け取ったとき、", l)
        if not m: sys.exit(f"{n}行: 受信節の頭のはずが「{l}」")
        scope = set(fields) | ({m.group(2)} if m.group(2) else set())
        body = parse_block(L, ("以上。",), scope)
        L.expect("以上。")
        handlers.append((m.group(1), m.group(2), body))
    L.next()
    return name, fields, inits, handlers

def parse_block(L, enders, scope=None):
    scope = set() if scope is None else scope   # すでにある名前（状態・引数・名付け済み）
    out = []
    while L.peek() not in enders and L.peek() != "そうでなければ、":
        out.append(parse_stmt(L, scope))
    return out

def parse_stmt(L, scope):
    n, l = L.next()
    m = re.fullmatch(r"もし (.+?) が (.+?)( でない| より小さい)? ならば、", l)
    if m:
        kind = {None: "ならば", " でない": "でなければ", " より小さい": "より小さければ"}[m.group(3)]
        then = parse_block(L, ("以上。",), scope)
        els = None
        if L.peek() == "そうでなければ、":
            L.next(); els = parse_block(L, ("以上。",), scope)
        L.expect("以上。")
        return ("if", (m.group(1), m.group(2), kind), then, els)
    m = re.fullmatch(r"(.+?)から(.+)まで繰り返す。", l)
    if m:
        body = parse_block(L, ("以上。",), scope); L.expect("以上。")
        return ("loop", m.group(1), m.group(2), body)
    for pat, kind in [
        (r"(.+) を表示する。", "disp"),
        (r"(.+) の全員に(「.+?」)(?:と (.+) )?を送る。", "zenin"),
        (r"(.+) に それぞれ(「.+?」)(?:と (.+) )?を送る。", "each"),
        (r"(.+) に(「.+?」)(?:と (.+) )?を送る。", "send"),
        (r"(.+) に (.+) を追加する。", "push"),
        (r"(\S+) は (.+) の先頭を取り出す。", "take"),
        (r"(\S+) は 「(.+?)」の新しいアクター。", "new"),
        (r"(\S+?の .+? 番目) は (.+)。", "chg"),             # 配列の要素への代入
        (r"(\S+) は (\S+) 足す (.+)。", "add"),
        (r"(\S+) は (.+)。", "chg"),
    ]:
        m = re.fullmatch(pat, l)
        if not m: continue
        g = m.groups()
        if kind == "add" and g[0] != g[1]: continue          # 「X は Y 足す Z」は代入として読む
        if kind == "chg" and g[1] == "空の配列" and g[0] not in scope:
            kind = "array"                                     # 新しい名前に空の配列 → 用意して名付ける
        if kind in ("take", "new", "array"): scope.add(g[0])
        return (kind,) + g
    sys.exit(f"{n}行: 読めない文「{l}」")

# ───────────── 文章形式を書き出す ─────────────

def close_at(e, i):
    """e[i] の「（」に対応する「）」の位置"""
    d = 0
    for j in range(i, len(e)):
        if e[j] == "（": d += 1
        elif e[j] == "）":
            d -= 1
            if d == 0: return j
    return -1

def top(s, sep):
    """括弧の外にある最初の sep の位置"""
    d = 0
    for j, c in enumerate(s):
        if c == "（": d += 1
        elif c == "）": d -= 1
        elif d == 0 and s.startswith(sep, j): return j
    return -1

def arith(e):
    """全体が（…）なら (種類, A, B) を返す。種類は add / sub / mod、ただの括弧は ("paren", X)"""
    if not (e.startswith("（") and close_at(e, 0) == len(e) - 1): return None
    s = e[1:-1].strip()
    for sep, k in ((" 足す ", "add"), (" 引く ", "sub")):
        j = top(s, sep)
        if j >= 0: return (k, s[:j], s[j + len(sep):])
    if s.endswith(" で割った余り"):
        j = top(s, " を ")
        if j >= 0: return ("mod", s[:j], s[j + 3:-len(" で割った余り")])
    return ("paren", s)

def expr(e):
    """構造化形式の式 → 文章形式の式"""
    e = e.strip()
    if e == "自分": return "自分自身"
    a = arith(e)
    if a:
        if a[0] == "add": return f"（{expr(a[1])}に{expr(a[2])}を加えた数）"
        if a[0] == "sub": return f"（{expr(a[1])}から{expr(a[2])}を引いた数）"
        if a[0] == "mod": return f"（{expr(a[1])}を{expr(a[2])}で割った余り）"
        return expr(a[1])                                   # 繰り返しの範囲を囲んだだけの括弧
    if e.endswith(" の要素数"): return expr(e[:-len(" の要素数")]) + "の要素数"
    # 位置指定: 「X の N 番目」「X の （A 足す B） 番目」
    m = re.fullmatch(r"(.+?)の (.+) 番目", e)
    if m:
        idx = m.group(2).strip()
        if idx.isdigit(): pass
        elif arith(idx) and arith(idx)[0] != "paren": idx = expr(idx)
        else: idx = f"（{expr(idx)}）"
        return f"{expr(m.group(1))}の{idx}番目"
    return e

def exprs(s, strings=False):
    parts = [p for p in s.split(" と ")]
    return "と".join(expr(p) + ("という文字列" if strings and p.startswith("「") else "") for p in parts)

def clause(st, final):
    k, g = st[0], st[1:]
    V = lambda s, r: s if final else r
    if k == "disp":  return f"{exprs(g[0], True)}を{V('表示する', '表示し')}"
    arg = lambda a: f"と{expr(a)}" if a else ""
    if k == "send":  return f"{exprs(g[0])}に{g[1]}というメッセージ{arg(g[2])}を{V('送る', '送り')}"
    if k == "each":  return f"{exprs(g[0])}にそれぞれ{g[1]}というメッセージ{arg(g[2])}を{V('送る', '送り')}"
    if k == "zenin": return f"{expr(g[0])}の全員に{g[1]}というメッセージ{arg(g[2])}を{V('送る', '送り')}"
    if k == "push":  return f"{exprs(g[1])}を{expr(g[0])}の末尾に{V('追加する', '追加し')}"
    if k == "take":  return f"{expr(g[1])}の先頭から{g[0]}を{V('取り出す', '取り出し')}"
    if k == "new":   return f"{g[1]}というアクターを1つ生成し、{g[0]}と{V('名付ける', '名付け')}"
    if k == "array": return f"空の配列を用意し、{g[0]}と{V('名付ける', '名付け')}"
    if k == "add":   return f"{expr(g[0])}に{expr(g[2])}を{V('加える', '加え')}"
    if k == "chg":
        verb = ("設定する", "設定し") if "の" in g[0] else ("変更する", "変更し")
        return f"{exprs(g[0])}を{expr(g[1])}に{V(*verb)}"
    raise ValueError(k)

MAXJOIN = 3
simple = lambda st: st[0] not in ("if", "loop")

def sentences(stmts):
    """文の並び → 文章の文のリスト。単純な文は MAXJOIN 個までつなぐ。"""
    out, run = [], []
    def flush():
        while run:
            chunk = run[:MAXJOIN]; del run[:MAXJOIN]
            out.append("、".join(clause(s, i == len(chunk) - 1) for i, s in enumerate(chunk)) + "。")
    for st in stmts:
        if simple(st): run.append(st); continue
        flush(); out.extend(compound(st))
    flush()
    return out

def part(stmts):
    """条件・繰り返しの本体。一文に収まれば一文、収まらなければ「次のことを行う。…以上。」"""
    if 0 < len(stmts) <= MAXJOIN and all(map(simple, stmts)):
        return [sentences(stmts)[0]]
    return ["次のことを行う。"] + sentences(stmts) + ["以上。"]

def joined(prefix, lines):
    """先頭の文に前置き（「〜ならば、」など）を付ける"""
    return [prefix + lines[0]] + lines[1:]

def compound(st):
    if st[0] == "loop":
        return joined(f"{expr(st[1])}から{expr(st[2])}までの各番号について、", part(st[3]))
    _, (x, y, kind), then, els = st
    out = joined(f"{expr(x)}が{expr(y)}{kind}、", part(then))
    if els is not None:
        e = joined("そうでなければ、", part(els))
        if out[-1] == "以上。": out += e          # then がブロックなら「そうでなければ」は次の行から
        else: out[-1] += e[0]; out += e[1:]      # then が一文なら「…。そうでなければ、…」と同じ行に続ける
    return out

def emit(defs, body):
    out = []
    for name, fields, inits, handlers in defs:
        out.append(f"{name}というアクターを定義する。")
        out.append(f"{name}は{'と'.join(fields)}を持つ。")
        if inits:
            groups = []
            for f, v in inits:
                if groups and groups[-1][1] == v: groups[-1][0].append(f)
                else: groups.append(([f], v))
            items = [f"{'と'.join(fs)}の初期値は{expr(v)}" for fs, v in groups]
            out.append("とし、".join(items) + "とする。")
        for msg, param, hbody in handlers:
            out.append("")
            head = f"{name}が「{msg}」というメッセージ" + (f"と{param}" if param else "") + "を受け取ったとき、"
            out += joined(head, sentences(hbody) or ["。"])
        out += ["", f"これで{name}の定義を終わる。", ""]
    out += ["実行を始める。", ""] + sentences(body) + ["", "これで実行を終わる。"]
    return "\n".join(out) + "\n"

if __name__ == "__main__":
    text = open(sys.argv[1], encoding="utf-8").read() if len(sys.argv) > 1 else sys.stdin.read()
    sys.stdout.write(emit(*parse_program(Lines(text))))
