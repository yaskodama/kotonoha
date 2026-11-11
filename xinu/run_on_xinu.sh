#!/bin/sh
# ことのはのプログラムを C に変換して PC Xinu に組み込み、QEMU で起動して出力を見る。
#   ./run_on_xinu.sh ../例題/ハノイの塔.txt          # 画面なしで起動し、プログラムの出力だけ表示して止める
#   ./run_on_xinu.sh ../例題/ハノイの塔.txt -i       # 組み込んだあと、対話的に起動（xsh が使える。終了は Ctrl-A x）
set -eu
HERE="$(cd "$(dirname "$0")" && pwd)"
XINU="${XINU:-$HOME/projects/xinu-mac/xinu-vbox}"
node "$HERE/k2xinu.mjs" "$1" > "$HERE/kprog.c"
cp "$HERE/krt.c" "$HERE/krt.h" "$HERE/kprog.c" "$XINU/system/"
( cd "$XINU/compile" && make 2>&1 | grep -E 'error|Built' )
if [ "${2:-}" = "-i" ]; then
  exec qemu-system-i386 -kernel "$XINU/compile/xinu.elf" -serial mon:stdio -display none -no-reboot -nic user,model=e1000-82545em
fi
OUT="$(mktemp)"
qemu-system-i386 -kernel "$XINU/compile/xinu.elf" -serial "file:$OUT" -display none -no-reboot -nic user,model=e1000-82545em &
PID=$!
i=0; while [ $i -lt 60 ] && ! grep -q 'xsh \$' "$OUT" 2>/dev/null; do sleep 1; i=$((i+1)); done
kill $PID 2>/dev/null || true
# 「Cannot obtain an IP address」の次の行から、ロゴの前までがプログラムの出力
tr -d '\r' < "$OUT" | awk '/Cannot obtain an IP address/{f=1;next} /\[31;1m/{f=0} f' | sed '/^$/d'
rm -f "$OUT"
