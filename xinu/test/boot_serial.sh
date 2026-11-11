#!/bin/sh
# 画面なしで起動し、シリアルを unix ソケット $2 に出す（test/serial.py でコマンドを打つ）。QMP は $1
XINU="${XINU:-$HOME/projects/xinu-mac/xinu-vbox}"
rm -f "$1" "$2"
exec qemu-system-i386 -kernel "$XINU/compile/xinu.elf" -vga none -device VGA,vgamem_mb=32 -display none \
  -chardev socket,id=s0,path="$2",server=on,wait=off -serial chardev:s0 \
  -qmp "unix:$1,server,nowait" -drive file="${DISK:-$HOME/projects/xinu-mac/xinu-disk.img}",format=raw,if=ide,index=0 -nic user,model=e1000-82545em
