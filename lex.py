#!/usr/bin/env python3
"""ことのは（文章形式）の字句解析器。

文章形式のソースを読み、bison 解析器が読む字句列（1行1字句: 番号<TAB>行<TAB>文字列）を出す。
空白がない日本語を切るため、次の規則で最長一致する:
  - 予約語（下の KW）
  - 宣言された名前（アクター名・状態・受信の引数・「〜と名付ける」・「〜を取り出す」で導入される名前）
  - 数字列、「…」の文字列
「※」から行末までは注釈、「■」で始まる行は見出しとして読み飛ばす。改行・空白は意味を持たない。

使い方: python3 lex.py ソース.txt  [kotonoha.tab.h]
"""
import re, sys

KW = {
    "というアクターを定義する。": "K_DEFACTOR", "を持つ。": "K_HAS",
    "の初期値は": "K_INIT", "とし、": "K_TOSHI", "とする。": "K_TOSURU",
    "というメッセージ": "T_MSG", "を受け取ったとき、": "K_RECV",
    "これで": "KORE", "の定義を終わる。": "K_ENDDEF",
    "実行を始める。": "K_RUN", "実行を終わる。": "K_ENDRUN",
    "。": "MARU", "、": "TEN", "その後、": "SONOATO",
    "ならば、": "NARABA", "でなければ、": "DENAKEREBA", "より小さければ、": "YORICHIISA",
    "そうでなければ、": "SOUDENAKEREBA", "次のことを行う。": "K_BLOCK", "以上。": "IJOU",
    "から": "KARA", "までの各番号について、": "MADE_NITSUITE",
    "は": "WA", "と": "TO", "が": "GA", "に": "NI", "を": "WO", "の": "NO",
    "の末尾": "NO_MATSUBI", "の先頭から": "NO_SENTOU_KARA", "の全員": "NO_ZENIN",
    "番目": "BANME", "それぞれ": "SOREZORE", "という文字列": "T_MOJIRETSU",
    "というアクター": "T_ACTOR", "1つ": "ICHITSU",
    "表示する": "HYOUJI_S", "表示し": "HYOUJI_R", "送る": "OKURU_S", "送り": "OKURU_R",
    "変更する": "HENKOU_S", "変更し": "HENKOU_R", "設定する": "HENKOU_S", "設定し": "HENKOU_R",
    "加える": "KUWAE_S", "加え": "KUWAE_R", "加えた数": "KUWAETA",
    "引いた数": "HIITA", "で割った余り": "WARIAMARI", "の要素数": "NO_YOUSOSU",
    "追加する": "TSUIKA_S", "追加し": "TSUIKA_R", "取り出す": "TORIDASU_S", "取り出し": "TORIDASU_R",
    "名付ける": "NAZUKE_S", "名付け": "NAZUKE_R", "生成し": "SEISEI_R", "用意し": "YOUI_R",
    "はい": "HAI", "いいえ": "IIE", "なし": "NASHI", "空": "SORA", "空の配列": "SORA_HAIRETSU",
    "自分": "JIBUN", "自分自身": "JIBUN_JISHIN", "現在の番号": "GENZAI", "その": "SONO",
    "（": "LP", "）": "RP",
}

def strip(src):
    """注釈と見出しを除き、各文字に元の行番号を付けた (文字列, 行番号表) を返す。"""
    chars, lines, instr = [], [], False
    for ln, line in enumerate(src.split("\n"), 1):
        if line.lstrip().startswith("■"):
            continue
        line = line.split("※", 1)[0]
        for c in line:
            if c == "「": instr = True
            elif c == "」": instr = False
            if instr or not c.isspace():      # 「…」の中の空白は文字列の一部として残す
                chars.append(c); lines.append(ln)
    return "".join(chars), lines

def declared_names(t):
    names = set()
    names |= set(re.findall(r"([^。、]+?)というアクターを定義する", t))
    for decl in re.findall(r"[^。、]+?は([^。]+?)を持つ。", t):
        names |= set(decl.split("と"))
    names |= set(re.findall(r"というメッセージと([^。、]+?)を受け取ったとき", t))
    names |= set(re.findall(r"、([^、。]+?)と名付け", t))
    names |= set(re.findall(r"の先頭から([^、。]+?)を取り出", t))
    return names

def token_codes(hpath):
    codes = {}
    for m in re.finditer(r"^\s+(\w+) = (\d+),?", open(hpath, encoding="utf-8").read(), re.M):
        codes[m.group(1)] = int(m.group(2))
    return codes

def lex(src):
    t, lines = strip(src)
    names = declared_names(t)
    table = [(k, v) for k, v in KW.items()] + [(n, "NAME") for n in names]
    table.sort(key=lambda kv: -len(kv[0]))
    i, out = 0, []
    while i < len(t):
        if t[i] == "「":
            j = t.index("」", i)
            out.append(("STRING", t[i:j + 1], lines[i])); i = j + 1; continue
        best = None
        for k, v in table:
            if t.startswith(k, i):
                best = (k, v); break          # 長い順に並べてあるので最初の一致が最長
        m = re.match(r"[0-9]+", t[i:])
        if m and (best is None or len(m.group()) > len(best[0])):
            out.append(("NUMBER", m.group(), lines[i])); i += len(m.group()); continue
        if best is None:
            sys.exit(f"字句エラー {lines[i]}行: 「{t[i:i+12]}…」は予約語でも宣言された名前でもない")
        out.append((best[1], best[0], lines[i])); i += len(best[0])
    return out, names

if __name__ == "__main__":
    src = open(sys.argv[1], encoding="utf-8").read()
    hpath = sys.argv[2] if len(sys.argv) > 2 else __file__.rsplit("/", 1)[0] + "/kotonoha.tab.h"
    codes = token_codes(hpath)
    toks, names = lex(src)
    for kind, text, ln in toks:
        print(f"{codes[kind]}\t{ln}\t{text}")
