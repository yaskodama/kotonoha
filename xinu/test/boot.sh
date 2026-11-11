#!/bin/sh
# 画面なしで GUI 付き Xinu を起動する（QMP: $1、シリアル: $2）
XINU="${XINU:-$HOME/projects/xinu-mac/xinu-vbox}"
rm -f "$1" "$2"
exec qemu-system-i386 -kernel "$XINU/compile/xinu.elf" -vga none -device VGA,vgamem_mb=32 -display none -serial "file:$2" \
  -qmp "unix:$1,server,nowait" -drive file="${DISK:-$HOME/projects/xinu-mac/xinu-disk.img}",format=raw,if=ide,index=0 -nic user,model=e1000-82545em
