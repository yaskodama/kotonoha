// 実行系の検査: 哲学者（安全版）を多数の種で走らせ、毎回全員が3回食べて満腹で終わるか。デッドロック版は止まる種があるか。
import { readFileSync } from "fs";
import { createRequire } from "module";
const K = createRequire(import.meta.url)("./kotonoha.js");
function run(file, seed, order = "random") {
  const r = K.makeRun(readFileSync(file, "utf8"), { seed, order, limit: 100000 });
  let lines = [], res;
  do { res = r.step(1000); lines.push(...res.lines.map(l => l.text)); } while (!res.done);
  return { lines, res, waiting: r.waiting() };
}
const N = +process.argv[2] || 1000;
for (const [file, label] of [["../哲学者_文章形式.txt", "安全版"], ["../tests/哲学者_デッドロック版.txt", "左から取る版"]]) {
  let full = 0, stuck = 0, err = 0, eatsMax = 0, firstStuck = null, maxPar = 0;
  for (let s = 1; s <= N; s++) {
    const { lines, res, waiting } = run(file, s);
    if (res.error) { err++; if (err < 3) console.log(label, "seed", s, res.error); continue; }
    const eats = lines.filter(l => l.endsWith("食事しています")).length, sat = lines.filter(l => l.endsWith("満腹です")).length;
    eatsMax = Math.max(eatsMax, eats);
    if (eats === 15 && sat === 5) full++; else { stuck++; if (!firstStuck) firstStuck = { s, eats, waiting }; }
  }
  console.log(`${label}: ${N}種 中 全員満腹 ${full} / 途中で止まった ${stuck} / エラー ${err}`);
  if (firstStuck) console.log("  止まった最初の種", firstStuck.s, "食事", firstStuck.eats, "回;", firstStuck.waiting.join(" ／ "));
}
const f = run("../哲学者_文章形式.txt", 0, "fifo");
console.log("届いた順:", f.lines.length, "行, 最後:", f.lines.slice(-2).join(" / "), f.res.error || "");
const h = run("../tests/あいさつ.txt", 1); console.log("あいさつ:", h.lines);
