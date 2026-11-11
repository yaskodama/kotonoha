// JS 版と C/Python 版の出力を突き合わせる
import { readFileSync } from "fs";
import { execSync } from "child_process";
import { createRequire } from "module";
const K = createRequire(import.meta.url)("./kotonoha.js");
const files = process.argv.slice(2);
let ng = 0;
for (const f of files) {
  const src = readFileSync(f, "utf8");
  let cK, jK, cB, jB, cErr = null, jErr = null;
  try { cK = execSync(`python3 ../lex.py "${f}" ../kotonoha.tab.h | ../kotonoha`, { encoding: "utf8", stdio: ["pipe", "pipe", "pipe"] }); }
  catch (e) { cErr = (e.stderr || "").trim(); }
  try { jK = K.toKozo(src); } catch (e) { jErr = e.message; }
  if (cErr || jErr) {
    const ok = !!cErr && !!jErr;
    console.log(`${ok ? "OK" : "NG"} ${f}  両方エラー? C:[${cErr}] JS:[${jErr}]`); if (!ok) ng++; continue;
  }
  cB = execSync(`python3 ../to_bunsho.py`, { input: cK, encoding: "utf8" });
  jB = K.toBunsho(jK);
  const a = cK === jK, b = cB === jB;
  console.log(`${a && b ? "OK" : "NG"} ${f}  文章→構造 一致:${a}  構造→文章 一致:${b}`);
  if (!(a && b)) ng++;
}
process.exit(ng ? 1 : 0);
