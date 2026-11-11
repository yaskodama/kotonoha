#!/usr/bin/env python3
"""Xinu のシリアル（QEMU -serial unix:SOCK,server）にコマンドを打って、出力を集める。
   serial.py SOCK "koto ls" "koto run x.txt" …   各コマンドのあと、次の「xsh $」まで（最長 T 秒）待つ"""
import socket, sys, time, os
s = socket.socket(socket.AF_UNIX); s.connect(sys.argv[1]); s.settimeout(0.2)
T = float(os.environ.get("T", "60"))
buf = b""
def until(pat, t):
    global buf
    end = time.time() + t
    while time.time() < end:
        try:
            d = s.recv(65536)
            if d: buf += d
        except socket.timeout: pass
        if pat in buf: return True
    return False
until(b"xsh $ ", 90); buf = b""
for c in sys.argv[2:]:
    for ch in (c + "\r").encode(): s.send(bytes([ch])); time.sleep(0.003)
    until(b"xsh $ ", T)
    sys.stdout.write(buf.decode("utf-8", "replace").replace("\r", "")); sys.stdout.flush(); buf = b""
