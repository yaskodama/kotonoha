// ことのは版 Xinu を JS の実行系で走らせる: node kx_run.mjs 核.txt 見本.txt [fifo|seed]
import { readFileSync } from "fs";
import { createRequire } from "module";
const K = createRequire(import.meta.url)("./kotonoha.js");
const src = process.argv.slice(2).filter(f => f.endsWith(".txt")).map(f => readFileSync(f, "utf8")).join("\n");
const o = process.argv.find(a => a === "fifo" || /^\d+$/.test(a));
const r = K.makeRun(src, o === "fifo" || !o ? { order: "fifo", limit: 200000 } : { seed: +o, limit: 200000 });
let res;
do { res = r.step(1000); res.lines.forEach(l => console.log(l.text)); } while (!res.done);
console.log("-- 処理したメッセージ", res.processed, res.error ? "誤り: " + res.error : "", res.stoppedByLimit ? "（上限）" : "");
const w = r.waiting(); if (w.length) console.log("待ち:", w.join(" / "));
