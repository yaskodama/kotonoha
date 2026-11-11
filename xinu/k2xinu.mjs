// k2xinu.mjs - ことのは（文章形式）を PC Xinu で動く C に変換する。
//   node k2xinu.mjs プログラム.txt 接頭辞 [表示名] > kp_接頭辞.c
// 生成物は struct kprogram 接頭辞_prog を一つ公開する（ソース本文・行と文の対応・停止点の表つき）。
// 構文木はブラウザ版の実行系（web/kotonoha.js）の解析器で作り、
// 式の読み方・名前の解決・代入の規則は同じ実行系の ev / assign / exec に合わせる。
import { readFileSync } from "fs";
import { createRequire } from "module";
const K = createRequire(import.meta.url)("../web/kotonoha.js");

const src = readFileSync(process.argv[2], "utf8");
const P = process.argv[3] || "kp0";
const TITLE = process.argv[4] || process.argv[2].split("/").pop().replace(/\.txt$/, "");
const kozoLines = K.toKozo(src).split("\n");
const stmtLines = new Set();
const [defs, main] = K._tree(src);
const arith = K._arith;

class CErr extends Error {}
const cstr = (s) => '"' + s.replace(/\\/g, "\\\\").replace(/"/g, '\\"') + '"';

// 名前の一覧（runtime.js の makeRun と同じ集め方）
const names = new Set(["自分"]);
defs.forEach((d) => { d[3].forEach((x) => { if (x[1]) names.add(x[1]); }); d[1].forEach((f) => names.add(f)); });
(function collect(stmts) {
  stmts.forEach((st) => {
    if (st[0] === "if") { collect(st[2]); if (st[3]) collect(st[3]); }
    else if (st[0] === "loop") collect(st[3]);
    else if (["take", "new", "array"].includes(st[0])) names.add(st[1]);
    else if (st[0] === "chg" && st[1].indexOf("の") < 0) st[1].split(" と ").forEach((n) => names.add(n.trim()));
  });
})(main.concat(...defs.map((d) => [].concat(...d[3].map((x) => x[2])))));
const byLen = [...names].sort((a, b) => b.length - a.length);
const classIdx = new Map(defs.map((d, i) => [d[0], i]));

function splitPath(e) {
  const segs = [];
  let pos = 0;
  while (pos < e.length) {
    const hit = byLen.find((n) => e.startsWith(n, pos) && (pos + n.length === e.length || e.startsWith("の", pos + n.length)));
    if (!hit) throw new CErr(`「${e}」の「${e.slice(pos)}」が読めない（宣言されていない名前）`);
    segs.push(hit); pos += hit.length;
    if (pos < e.length) pos += 1;
  }
  return segs;
}

// 文脈: cls＝受信節のアクター（実行部では null）、param＝受け取った名前、slots＝局所変数の番号、loops＝繰り返しの変数名
function isLocal(n, ctx) { return n === ctx.param || !ctx.cls || !ctx.cls[1].includes(n); }
function slot(n, ctx) {
  if (!ctx.slots.has(n)) ctx.slots.set(n, ctx.slots.size);
  return `L[${ctx.slots.get(n)}]`;
}
function nameRef(n, ctx, whole) {
  if (n === "自分") { if (!ctx.cls) throw new CErr("「実行を始める。」の中に自分は無い"); return "kactv(self)"; }
  if (isLocal(n, ctx)) return `kread(${slot(n, ctx)}, ${cstr(whole)})`;
  return `self->f[${ctx.cls[1].indexOf(n)}]`;
}

function ex(e, ctx) {
  e = e.trim();
  let m;
  const w = cstr(e);
  if (/^\d+$/.test(e)) return `kn(${e})`;
  if ((m = /^「(.*)」$/.exec(e))) return `ks(${cstr(m[1])})`;
  if (e === "はい") return "kb(1)";
  if (e === "いいえ") return "kb(0)";
  if (e === "なし") return "knone()";
  if (e === "空" || e === "空の配列") return "knewarr()";
  if (e === "現在の番号") { if (!ctx.loops.length) throw new CErr("繰り返しの外で「現在の番号」を使った"); return `kn(${ctx.loops[ctx.loops.length - 1]})`; }
  const a = arith(e);
  if (a) {
    if (a[0] === "paren") return ex(a[1], ctx);
    return `k${a[0]}(${ex(a[1], ctx)}, ${ex(a[2], ctx)}, ${w})`;
  }
  if (/ の要素数$/.test(e)) return `klen(${ex(e.slice(0, -" の要素数".length), ctx)}, ${w})`;
  if ((m = /^(.+?)の (.+) 番目$/.exec(e))) return `kget(${ex(m[1], ctx)}, ${ex(m[2], ctx)}, ${w})`;
  const segs = splitPath(e);
  let v = nameRef(segs[0], ctx, e);
  for (let i = 1; i < segs.length; i++) v = `(*kfield(${v}, ${cstr(segs[i])}, ${w}))`;
  return v;
}

function assign(target, val, ctx) {
  target = target.trim();
  const w = cstr(target);
  let m;
  if ((m = /^(.+?)の (.+) 番目$/.exec(target))) return `kset(${ex(m[1], ctx)}, ${ex(m[2], ctx)}, ${val}, ${w});`;
  const segs = splitPath(target);
  if (segs.length === 1) {
    const n = segs[0];
    if (isLocal(n, ctx)) return `${slot(n, ctx)} = ${val};`;
    return `self->f[${ctx.cls[1].indexOf(n)}] = ${val};`;
  }
  let obj = nameRef(segs[0], ctx, target);
  for (let i = 1; i < segs.length - 1; i++) obj = `(*kfield(${obj}, ${cstr(segs[i])}, ${w}))`;
  return `*kfield(${obj}, ${cstr(segs[segs.length - 1])}, ${w}) = ${val};`;
}

const list = (s) => s.split(" と ");
let tmp = 0;
function stmts(sts, ctx, ind) {
  const out = [];
  const p = (s) => out.push(ind + s);
  for (const st of sts) {
    const [k, ...g] = st;
    // デバッガの停止点: この文を実行する前に止まるかどうかを kstep が決める
    if (st.line) { stmtLines.add(st.line); p(`kstep(&KF[${ctx.fid}], ${st.line}, self, L);`); }
    if (k === "if") {
      const [a, b, kind] = g[0];
      const ca = ex(a, ctx), cb = ex(b, ctx);
      const cond = kind === "ならば" ? `keq(${ca}, ${cb})` : kind === "でなければ" ? `!keq(${ca}, ${cb})` : `klt(${ca}, ${cb}, ${cstr(a)}, ${cstr(b)})`;
      p(`if (${cond}) {`);
      out.push(...stmts(g[1], ctx, ind + "\t"));
      if (g[2]) { p("} else {"); out.push(...stmts(g[2], ctx, ind + "\t")); }
      p("}");
    } else if (k === "loop") {
      const v = `n${tmp++}`, hi = `h${tmp++}`;
      p(`{ int32 ${v}, ${hi} = knum(${ex(g[1], ctx)}, ${cstr(g[1])});`);
      p(`  for (${v} = knum(${ex(g[0], ctx)}, ${cstr(g[0])}); ${v} <= ${hi}; ${v}++) {`);
      ctx.loops.push(v);
      out.push(...stmts(g[2], ctx, ind + "\t"));
      ctx.loops.pop();
      p("} }");
    } else if (k === "disp") {
      const parts = list(g[0]);
      p(`{ static const int32 lit[${parts.length}] = { ${parts.map((x) => (x.trim().charAt(0) === "「" ? 1 : 0)).join(", ")} };`);
      p(`  kv vals[${parts.length}];`);
      parts.forEach((x, i) => p(`  vals[${i}] = ${ex(x, ctx)};`));
      p(`  kdisp(${parts.length}, lit, vals); }`);
    } else if (k === "send" || k === "each" || k === "zenin") {
      const msg = cstr(g[1].slice(1, -1)), arg = g[2] ? ex(g[2], ctx) : "knone()", has = g[2] ? 1 : 0;
      if (k === "zenin") p(`ksendall(${ex(g[0], ctx)}, ${msg}, ${arg}, ${has}, ${cstr(g[0])});`);
      else {
        // 引数は一度だけ計算して全員に同じ値を送る
        p(`{ kv a = ${arg};`);
        list(g[0]).forEach((x) => p(`  ksend(${ex(x, ctx)}, ${msg}, a, ${has});`));
        p("}");
      }
    } else if (k === "push") {
      p(`{ kv arr = ${ex(g[0], ctx)};`);
      list(g[1]).forEach((x) => p(`  kpush(arr, ${ex(x, ctx)}, ${cstr(g[0])});`));
      p("}");
    } else if (k === "take") p(assign(g[0], `kshift(${ex(g[1], ctx)}, ${cstr(g[1])})`, ctx));
    else if (k === "new") {
      if (!classIdx.has(g[1])) throw new CErr(`「${g[1]}」というアクターは定義されていない`);
      p(assign(g[0], `knew(&kcls${classIdx.get(g[1])})`, ctx));
    } else if (k === "array") p(assign(g[0], "knewarr()", ctx));
    else if (k === "add") p(assign(g[0], `kadd(${ex(g[0], ctx)}, ${ex(g[2], ctx)}, ${cstr(g[0])})`, ctx));
    else if (k === "chg") {
      p(`{ kv v = ${ex(g[1], ctx)};`);
      list(g[0]).forEach((t) => p("  " + assign(t, "v", ctx)));
      p("}");
    } else throw new CErr("知らない文 " + k);
  }
  return out;
}

// 関数一つ分: 本文を先に作り、使われた局所変数の数だけ L を用意する
const funs = [];   // { cls, msg, line, end, slots }
function func(head, body, ctx, meta) {
  ctx.fid = funs.length;
  const f = { ...meta, slots: null };
  funs.push(f);
  const lines = stmts(body, ctx, "\t");
  f.slots = [...ctx.slots.keys()];
  const n = Math.max(ctx.slots.size, 1);
  const pre = [`\tkv L[${n}];`, `\tint32 i;`, `\t(void)L;`, `\tfor (i = 0; i < ${n}; i++) L[i].t = KN_UNSET;`];
  if (ctx.param) pre.push(`\t${slot(ctx.param, ctx)} = arg;`);
  return [head + " {", ...pre, ...lines, "}", ""].join("\n");
}

const out = [];
try {
  out.push("/* " + P + ".c - ことのはから k2xinu.mjs で生成。手で直さないこと */");
  out.push("/* 元: " + process.argv[2].split("/").pop() + " */");
  out.push("#include <xinu.h>", '#include "krt.h"', "");
  out.push(`extern struct kprogram ${P}_prog;`);
  out.push("@@KFDECL@@");
  defs.forEach((d, ci) => out.push(`static struct kclass kcls${ci};`));
  out.push("");
  defs.forEach((d, ci) => {
    const [name, fields, inits, handlers] = d;
    // 初期値: 生成したアクター自身を self として、上から順に計算する
    const ictx = { cls: d, param: null, slots: new Map(), loops: [] };
    const ibody = inits.map(([f, e]) => `\tself->f[${fields.indexOf(f)}] = ${ex(e, ictx)};`);
    out.push(`static void kinit${ci}(struct kact *self) {`, ...ibody, "}", "");
    handlers.forEach((h, hi) => {
      const ctx = { cls: d, param: h[1], slots: new Map(), loops: [] };
      out.push(func(`static void kh${ci}_${hi}(struct kact *self, kv arg)`, h[2], ctx, { cls: ci, msg: h[0], line: h.line, end: h.end }));
    });
    out.push(`static const char *kf${ci}[] = { ${fields.map(cstr).join(", ")} };`);
    out.push(`static const struct khent kht${ci}[] = { ${handlers.map((h, hi) => `{ ${cstr(h[0])}, kh${ci}_${hi} }`).join(", ")} };`);
    out.push(`static struct kclass kcls${ci} = { ${cstr(name)}, ${fields.length}, kf${ci}, kinit${ci}, ${handlers.length}, kht${ci}, 0 };`, "");
  });
  const mctx = { cls: null, param: null, slots: new Map(), loops: [] };
  out.push(func("static void kbody(void)", main, mctx, { cls: -1, msg: "実行部", line: main.line, end: main.end })
    .replace("{\n", "{\n\tstruct kact *self = NULL; (void)self;\n"));

  // 関数の表（局所変数の名前つき）
  funs.forEach((f, i) => out.push(`static const char *KS${i}[] = { ${f.slots.length ? f.slots.map(cstr).join(", ") : '""'} };`));
  out.push(`static struct kfun KF[${funs.length}] = {`);
  funs.forEach((f, i) => out.push(`\t{ &${P}_prog, ${f.cls}, ${cstr(f.msg)}, ${f.line}, ${f.end}, ${f.slots.length}, KS${i} },`));
  out.push("};", "");
  // ソース: 構造化形式の各行（番号＝添字+1）、どの行に文があるか、停止点、元の文章形式
  const N = kozoLines.length;
  out.push(`static const char *KL[${N}] = {`, ...kozoLines.map((l) => "\t" + cstr(l) + ","), "};");
  const st = Array.from({ length: N + 1 }, (_, i) => (stmtLines.has(i) ? 1 : 0));
  out.push(`static const unsigned char KST[${N + 1}] = { ${st.join(",")} };`);
  out.push(`static unsigned char KBP[${N + 1}];`);
  const srcLines = src.replace(/\n+$/, "").split("\n");
  out.push(`static const char *KSRC[${srcLines.length}] = {`, ...srcLines.map((l) => "\t" + cstr(l) + ","), "};");
  out.push(`static struct kclass *KC[${Math.max(defs.length, 1)}] = { ${defs.length ? defs.map((d, ci) => `&kcls${ci}`).join(", ") : "NULL"} };`);
  out.push(`static const int32 KCL[${Math.max(defs.length, 1)}] = { ${defs.map((d) => d.line).join(", ") || 0} };`);
  out.push(`static const int32 KCE[${Math.max(defs.length, 1)}] = { ${defs.map((d) => d.end).join(", ") || 0} };`);
  out.push(`struct kprogram ${P}_prog = { ${cstr(TITLE)}, ${defs.length}, KC, KCL, KCE, kbody, ${main.line}, ${main.end},`,
    `\t${N}, KL, KST, KBP, ${srcLines.length}, KSRC, ${funs.length}, KF };`);
} catch (e) {
  if (e instanceof CErr) { console.error("変換エラー: " + e.message); process.exit(1); }
  throw e;
}
console.log(out.join("\n").replace("@@KFDECL@@", `static struct kfun KF[${funs.length}];`));
