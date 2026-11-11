#!/usr/bin/env python3
"""Xinu 自身のソースを C の表にして埋め込む（kxsrc.c を生成）。
   gen_xsrc.py XINU_DIR OUT.c
ディレクトリ → ファイル → 関数（C の関数定義と、アセンブラの .globl の札）の三段で引けるようにする。
タブは 8 桁で空白に直す。行は UTF-8 のまま（解釈できないバイトは ? に置き換える）。"""
import os, re, sys

XINU, OUT = sys.argv[1], sys.argv[2]
DIRS = ["system", "include", "shell", "lib", "net",
        "device/tty", "device/eth", "device/lfs", "device/rfs", "device/rds", "device/ram",
        "device/nam", "device/pipe", "device/sdmc", "config"]
SKIP = re.compile(r"^(jpfont\.c|kp\d+\.c|kxsrc\.c|kprogs\.c|kxc\.tab\.[ch]|y\.tab\.[ch]|lex\.yy\.c)$")
EXT = (".c", ".h", ".S", ".s", ".y", ".l")

def cstr(s):
    out = []
    for ch in s:
        if ch == "\\": out.append("\\\\")
        elif ch == '"': out.append('\\"')
        elif ord(ch) < 32: out.append(" ")
        else: out.append(ch)
    # 三文字表記（??=）を避ける
    return '"' + "".join(out).replace("??", '?""?') + '"'

FN_HEAD = re.compile(r"^[A-Za-z_][\w \t\*]*?\b([A-Za-z_]\w*)\s*\(")
def functions(lines, name):
    """C の関数定義（Xinu の書き方: 型と名前が行頭、本体の { と } も行頭）と、アセンブラの大域の札"""
    fns = []
    if name.endswith((".S", ".s")):
        globs = set(m.group(1) for l in lines for m in [re.match(r"\s*\.globl\s+(\w+)", l)] if m)
        cur = None
        for i, l in enumerate(lines, 1):
            m = re.match(r"^(\w+):", l)
            if m and m.group(1) in globs:
                if cur: cur[2] = i - 1
                cur = [m.group(1), i, len(lines)]
                fns.append(cur)
        return [tuple(f) for f in fns]
    i = 0
    n = len(lines)
    while i < n:
        l = lines[i]
        m = FN_HEAD.match(l)
        if m and not l.rstrip().endswith(";") and not l.startswith(("#", "typedef", "struct", "extern", "static\tconst", "return")) \
                and m.group(1) not in ("if", "while", "for", "switch", "sizeof", "return"):
            # 次の 20 行以内に行頭の { があり、その前に ; で終わる行頭の宣言が無ければ関数
            j = i
            ok = False
            while j < min(n, i + 20):
                if lines[j].startswith("{"): ok = True; break
                if j > i and lines[j].rstrip().endswith(";") and not lines[j].startswith((" ", "\t")): break
                j += 1
            if ok:
                k = j + 1
                while k < n and not lines[k].startswith("}"): k += 1
                fns.append((m.group(1), i + 1, min(k + 1, n)))
                i = k + 1
                continue
        i += 1
    return fns

files = []   # (dir, name, lines, fns)
for d in DIRS:
    p = os.path.join(XINU, d)
    if not os.path.isdir(p): continue
    for name in sorted(os.listdir(p)):
        if not name.endswith(EXT) or SKIP.match(name): continue
        if d == "config" and name not in ("Configuration", "config.y", "config.l"): continue
        raw = open(os.path.join(p, name), "rb").read().decode("utf-8", "replace").replace("�", "?")
        lines = [l.expandtabs(8).rstrip() for l in raw.replace("\r", "").split("\n")]
        while lines and lines[-1] == "": lines.pop()
        files.append((d, name, lines, functions(lines, name)))
    if d == "config":
        q = os.path.join(p, "Configuration")
        if os.path.exists(q) and not any(f[1] == "Configuration" for f in files):
            raw = open(q, "rb").read().decode("utf-8", "replace")
            lines = [l.expandtabs(8).rstrip() for l in raw.split("\n")]
            files.append((d, "Configuration", lines, []))

dirs = []
for f in files:
    if f[0] not in dirs: dirs.append(f[0])

with open(OUT, "w", encoding="utf-8") as o:
    o.write("/* kxsrc.c - Xinu 自身のソース（gen_xsrc.py が生成。手で直さない） */\n#include <xinu.h>\n#include \"kxsrc.h\"\n\n")
    for i, (d, name, lines, fns) in enumerate(files):
        o.write("static const char *const L%d[%d] = {\n" % (i, max(len(lines), 1)))
        for l in lines or [""]: o.write("\t" + cstr(l) + ",\n")
        o.write("};\n")
        if fns:
            o.write("static const struct xfn F%d[%d] = { %s };\n" % (i, len(fns), ", ".join(
                "{ %s, %d, %d }" % (cstr(fn), a, b) for fn, a, b in fns)))
    o.write("const struct xfile xfiles[%d] = {\n" % len(files))
    for i, (d, name, lines, fns) in enumerate(files):
        o.write("\t{ %d, %s, %d, L%d, %d, %s },\n" % (dirs.index(d), cstr(name), max(len(lines), 1), i, len(fns), "F%d" % i if fns else "NULL"))
    o.write("};\nconst int32 nxfiles = %d;\n" % len(files))
    o.write("const char *const xdirs[%d] = { %s };\nconst int32 nxdirs = %d;\n" % (len(dirs), ", ".join(cstr(d) for d in dirs), len(dirs)))
total = sum(len(f[2]) for f in files)
print("kxsrc: %d dirs, %d files, %d lines, %d functions" % (len(dirs), len(files), total, sum(len(f[3]) for f in files)))

# ───── ことのはで書き直した Xinu（kxinu/）: 「※【system/xxx.c】題」の印で、元の C のファイルと関数に対応づける ─────
if len(sys.argv) > 3:
    KX = sys.argv[3]
    GROUPS = [("system/（核）", "核.txt", "Xinu（ことのは版）挨拶"),
              ("見本1: 挨拶", "見本_挨拶.txt", "Xinu（ことのは版）挨拶"),
              ("見本2: 生産と消費", "見本_生産と消費.txt", "Xinu（ことのは版）生産と消費")]
    HEAD = re.compile(r"^(\S+?)が「(.+?)」というメッセージ(?:と\S+?)?を受け取ったとき")
    MARK = re.compile(r"^※【(.+?)】\s*([^\s：]+)")
    kfiles = []   # (grp, path, [(from,to)], [(fn, a, b)])
    for gi, (gname, fname, prog) in enumerate(GROUPS):
        lines = open(os.path.join(KX, fname), encoding="utf-8").read().rstrip("\n").split("\n")
        marks = [i for i, l in enumerate(lines) if MARK.match(l)]
        for k, mi in enumerate(marks):
            path, title = MARK.match(lines[mi]).groups()
            end = (marks[k + 1] if k + 1 < len(marks) else len(lines)) - 1
            while end > mi and lines[end].strip() == "": end -= 1
            heads = [i for i in range(mi, end + 1) if HEAD.match(lines[i])]
            fns = []
            for h, hi in enumerate(heads):
                cls, msg = HEAD.match(lines[hi]).groups()
                e = (heads[h + 1] - 1) if h + 1 < len(heads) else end
                while e > hi and (lines[e].strip() == "" or re.match(r"^これで.+の定義を終わる。", lines[e])): e -= 1
                fns.append((msg if cls == "カーネル" else "%s「%s」" % (cls, msg), hi + 1, e + 1))
            if not heads: fns.append((title, mi + 1, end + 1))
            f = next((f for f in kfiles if f[0] == gi and f[1] == path), None)
            if not f:
                f = (gi, path, [], []); kfiles.append(f)
            f[2].append((mi + 1, end + 1)); f[3].extend(fns)
        GROUPS[gi] = (gname, lines, prog)
    with open(OUT, "a", encoding="utf-8") as o:
        o.write("\n/* ことのはで書き直した Xinu */\n")
        for gi, (gname, lines, prog) in enumerate(GROUPS):
            o.write("static const char *const KXL%d[%d] = {\n" % (gi, len(lines)))
            for l in lines: o.write("\t" + cstr(l.expandtabs(8)) + ",\n")
            o.write("};\n")
        o.write("const struct kxgrp kxgrps[%d] = {\n" % len(GROUPS))
        for gi, (gname, lines, prog) in enumerate(GROUPS):
            o.write("\t{ %s, %s, %d, KXL%d },\n" % (cstr(gname), cstr(prog), len(lines), gi))
        o.write("};\nconst int32 nkxgrps = %d;\n" % len(GROUPS))
        for i, (gi, path, secs, fns) in enumerate(kfiles):
            o.write("static const struct xfn KXF%d[%d] = { %s };\n" % (i, len(fns), ", ".join("{ %s, %d, %d }" % (cstr(n), a, b) for n, a, b in fns)))
        o.write("const struct kxfile kxfiles[%d] = {\n" % len(kfiles))
        for i, (gi, path, secs, fns) in enumerate(kfiles):
            secs = (secs + [(0, 0)] * 4)[:4]
            o.write("\t{ %d, %s, %d, { %s }, %d, KXF%d },\n" % (gi, cstr(path), min(len(secs), 4),
                    ", ".join("{ %d, %d }" % s for s in secs), len(fns), i))
        o.write("};\nconst int32 nkxfiles = %d;\n" % len(kfiles))
    print("kxinu: %d groups, %d files, %d functions" % (len(GROUPS), len(kfiles), sum(len(f[3]) for f in kfiles)))
    for f in kfiles: print("  ", f[0], f[1], [x[0] for x in f[3]])
