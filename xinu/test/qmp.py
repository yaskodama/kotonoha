#!/usr/bin/env python3
"""QEMU を QMP で操る小道具（画面写し・マウス・キー）。
   qmp.py SOCK shot out.png | click X Y | move X Y | key NAME | wheel X Y DZ  （複数をつなげて書ける）"""
import socket, json, sys, time, subprocess, os
SOCK = sys.argv[1]
s = socket.socket(socket.AF_UNIX); s.connect(SOCK); f = s.makefile('rw')
def rd():
    while True:
        m = json.loads(f.readline())
        if 'return' in m or 'error' in m: return m
def cmd(c, **a):
    f.write(json.dumps({"execute": c, "arguments": a} if a else {"execute": c}) + "\n"); f.flush(); return rd()
json.loads(f.readline()); cmd("qmp_capabilities")
W, H = 1440, 900   # 論理の画面（表は縦横2倍）
def absxy(x, y): return [{"type": "abs", "data": {"axis": "x", "value": int(x * 32767 / (W - 1))}},
                        {"type": "abs", "data": {"axis": "y", "value": int(y * 32767 / (H - 1))}}]
def btn(down): return [{"type": "btn", "data": {"down": down, "button": "left"}}]
a = sys.argv[2:]; i = 0
while i < len(a):
    op = a[i]
    if op == "shot":
        out = a[i+1]; ppm = out + ".ppm"; cmd("screendump", filename=ppm)
        time.sleep(0.3); subprocess.run(["sips", "-s", "format", "png", ppm, "--out", out], capture_output=True); os.remove(ppm); i += 2
    elif op == "move":
        cmd("input-send-event", events=absxy(float(a[i+1]), float(a[i+2]))); i += 3; time.sleep(0.15)
    elif op == "click":
        x, y = float(a[i+1]), float(a[i+2])
        cmd("input-send-event", events=absxy(x, y)); time.sleep(0.15)
        cmd("input-send-event", events=btn(True)); time.sleep(0.15)
        cmd("input-send-event", events=btn(False)); time.sleep(0.3); i += 3
    elif op == "drag":
        x0, y0, x1, y1 = map(float, a[i+1:i+5])
        cmd("input-send-event", events=absxy(x0, y0)); time.sleep(0.15)
        cmd("input-send-event", events=btn(True)); time.sleep(0.15)
        for k in range(1, 6):
            cmd("input-send-event", events=absxy(x0 + (x1-x0)*k/5, y0 + (y1-y0)*k/5)); time.sleep(0.08)
        cmd("input-send-event", events=btn(False)); time.sleep(0.3); i += 5
    elif op == "key":
        cmd("send-key", keys=[{"type": "qcode", "data": a[i+1]}]); time.sleep(0.3); i += 2
    elif op == "wheel":
        x, y, dz = float(a[i+1]), float(a[i+2]), int(a[i+3])
        cmd("input-send-event", events=absxy(x, y)); time.sleep(0.15)
        for k in range(abs(dz)):
            b = "wheel-down" if dz > 0 else "wheel-up"
            cmd("input-send-event", events=[{"type": "btn", "data": {"down": True, "button": b}}])
            cmd("input-send-event", events=[{"type": "btn", "data": {"down": False, "button": b}}]); time.sleep(0.1)
        i += 4
    elif op == "sleep":
        time.sleep(float(a[i+1])); i += 2
    else:
        print("unknown", op); i += 1
