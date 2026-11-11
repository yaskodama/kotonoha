#!/bin/sh
# ことのはの開発環境を PC Xinu に組み込んでビルドする。
#   ./install.sh            … 例題をすべて変換し、実行時ライブラリ・ウィンドウシステムと一緒にビルド
# 組み込み先: $XINU（既定 ~/projects/xinu-mac/xinu-vbox）
set -eu
HERE="$(cd "$(dirname "$0")" && pwd)"
XINU="${XINU:-$HOME/projects/xinu-mac/xinu-vbox}"
K="$HERE/.."
SYS="$XINU/system"

# 0) ことのは版 Xinu: 核（kxinu/核.txt）と見本をつないで一本のプログラムにする
mkdir -p "$HERE/kxinu/build"
for s in 挨拶 生産と消費; do
  cat "$HERE/kxinu/核.txt" "$HERE/kxinu/見本_$s.txt" > "$HERE/kxinu/build/Xinu_$s.txt"
done

# 1) プログラムを C に変換（kp0.c, kp1.c, …）と、その一覧 kprogs.c
rm -f "$SYS"/kp[0-9]*.c "$SYS/kprog.c"
i=0
TABLE=""
for f in "$K/例題/Xinuの挨拶.txt" "$K/例題/ハノイの塔.txt" "$K/例題/ユークリッドの互除法.txt" \
         "$K/例題/バブルソート.txt" "$K/例題/クイックソート.txt" \
         "$K/哲学者_文章形式.txt:5人の哲学者" "$K/tests/哲学者_デッドロック版.txt:哲学者（デッドロック版）" \
         "$HERE/kxinu/build/Xinu_挨拶.txt:Xinu（ことのは版）挨拶" \
         "$HERE/kxinu/build/Xinu_生産と消費.txt:Xinu（ことのは版）生産と消費" ${EXTRA:-}; do
  path="${f%%:*}"; name=""
  case "$f" in *:*) name="${f#*:}";; esac
  node "$HERE/k2xinu.mjs" "$path" "kp$i" $name > "$SYS/kp$i.c"
  TABLE="$TABLE &kp${i}_prog,"
  i=$((i+1))
done
{
  echo '/* kprogs.c - 組み込んだことのはのプログラムの一覧（install.sh が生成） */'
  echo '#include <xinu.h>'
  echo '#include "krt.h"'
  j=0; while [ $j -lt $i ]; do echo "extern struct kprogram kp${j}_prog;"; j=$((j+1)); done
  echo "struct kprogram *kprogs[32] = {$TABLE };	/* Xinu の中でコンパイルしたものを後ろに足す（KPROGS_MAX） */"
  echo "int32 nkprogs = $i;"
} > "$SYS/kprogs.c"

# 2) 実行時ライブラリとウィンドウシステム
cp "$HERE/krt.c" "$HERE/krt.h" "$SYS/"
cp "$HERE/gui/gfx.c" "$HERE/gui/gfx.h" "$HERE/gui/input.c" "$HERE/gui/input.h" \
   "$HERE/gui/wm.c" "$HERE/gui/wm.h" "$HERE/gui/kgui.c" "$HERE/gui/jpfont.c" "$HERE/gui/kxsrc.h" "$SYS/"

# 2a) Xinu の中のコンパイラ（kxc/）とファイルシステム（fs/）。文法は bison 3.8 で C にする
BISON="${BISON:-/opt/homebrew/opt/bison/bin/bison}"
"$BISON" -Wall -o "$HERE/kxc/kxc.tab.c" --header="$HERE/kxc/kxc.tab.h" "$HERE/kxc/kxc.y"
cp "$HERE/kxc/kxc.h" "$HERE/kxc/kxc.tab.c" "$HERE/kxc/kxc.tab.h" "$HERE/kxc/kxlex.c" "$HERE/kxc/kxcomp.c" "$HERE/kxc/kxfiles.c" \
   "$HERE/fs/kfs.c" "$HERE/fs/kfs.h" "$SYS/"
cp "$HERE/kxc/xsh_koto.c" "$SYS/"

# 2b) Xinu 自身のソースを埋め込む（ブラウザの「Xinu ソース」タブ）。上で写したファイルも含む
python3 "$HERE/gui/tools/gen_xsrc.py" "$XINU" "$SYS/kxsrc.c" "$HERE/kxinu"

# 3) ビルド
# 新しいファイルが増えると、最初の make は .defs を作り直すだけで失敗することがあるので、もう一度だけ試す
( cd "$XINU/compile" && { make > "$XINU/compile/kotonoha_make.log" 2>&1 || make > "$XINU/compile/kotonoha_make.log" 2>&1; } ) || { grep -E 'error' "$XINU/compile/kotonoha_make.log"; exit 1; }
grep -E 'Built' "$XINU/compile/kotonoha_make.log"
