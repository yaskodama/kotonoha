import { readFileSync, writeFileSync, mkdirSync } from "fs";
import { execSync } from "child_process";
import { createRequire } from "module";
const K = createRequire(import.meta.url)("./kotonoha.js");
const base = readFileSync("../哲学者_文章形式.txt", "utf8");
const sents = base.split(/(?<=。)/);            // 「。」で切った断片
let seed = 12345; const rnd = n => (seed = (seed * 1103515245 + 12345) % 2147483648) % n;
const dir = process.env.TMPD; mkdirSync(dir, { recursive: true });
let agree = 0, accepted = 0, rejected = 0, bad = [];
for (let t = 0; t < 300; t++) {
  const s = sents.slice(); const op = t % 3, i = rnd(s.length), j = rnd(s.length);
  if (op === 0) s.splice(i, 1); else if (op === 1) [s[i], s[j]] = [s[j], s[i]]; else s.splice(i, 0, s[j]);
  const src = s.join(""), f = `${dir}/m${t}.txt`; writeFileSync(f, src);
  let c = null, j2 = null;
  try { c = execSync(`python3 ../lex.py ${f} ../kotonoha.tab.h | ../kotonoha`, { encoding: "utf8", stdio: ["pipe","pipe","pipe"] }); } catch { c = "ERR"; }
  try { j2 = K.toKozo(src); } catch { j2 = "ERR"; }
  if (c === j2) { agree++; c === "ERR" ? rejected++ : accepted++; }
  else bad.push(t);
}
console.log(`300本中 一致 ${agree}（通った ${accepted}／弾いた ${rejected}）  不一致 ${bad.length} ${bad.slice(0,10)}`);
