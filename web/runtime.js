/* ことのは ブラウザ版の実行部（kotonoha_parser.js＝jison が kotonoha.y から生成 の後ろに連結する）
 *   Kotonoha.toKozo(文章形式)  → 構造化形式   （lex.py ＋ bison 解析器 と同じ結果を出す）
 *   Kotonoha.toBunsho(構造化形式) → 文章形式   （to_bunsho.py と同じ結果を出す）
 */
var Kotonoha = (function () {
  "use strict";

  /* ───── 字句解析（lex.py の写し） ───── */
  var KW = {
    "というアクターを定義する。": "K_DEFACTOR", "を持つ。": "K_HAS",
    "の初期値は": "K_INIT", "とし、": "K_TOSHI", "とする。": "K_TOSURU",
    "というメッセージ": "T_MSG", "を受け取ったとき、": "K_RECV",
    "これで": "KORE", "の定義を終わる。": "K_ENDDEF",
    "実行を始める。": "K_RUN", "実行を終わる。": "K_ENDRUN",
    "。": "MARU", "、": "TEN", "その後、": "SONOATO",
    "ならば、": "NARABA", "でなければ、": "DENAKEREBA", "より小さければ、": "YORICHIISA",
    "そうでなければ、": "SOUDENAKEREBA", "次のことを行う。": "K_BLOCK", "以上。": "IJOU",
    "から": "KARA", "までの各番号について、": "MADE_NITSUITE",
    "は": "WA", "と": "TO", "が": "GA", "に": "NI", "を": "WO", "の": "NO",
    "の末尾": "NO_MATSUBI", "の先頭から": "NO_SENTOU_KARA", "の全員": "NO_ZENIN",
    "番目": "BANME", "それぞれ": "SOREZORE", "という文字列": "T_MOJIRETSU",
    "というアクター": "T_ACTOR", "1つ": "ICHITSU",
    "表示する": "HYOUJI_S", "表示し": "HYOUJI_R", "送る": "OKURU_S", "送り": "OKURU_R",
    "変更する": "HENKOU_S", "変更し": "HENKOU_R", "設定する": "HENKOU_S", "設定し": "HENKOU_R",
    "加える": "KUWAE_S", "加え": "KUWAE_R", "加えた数": "KUWAETA",
    "引いた数": "HIITA", "で割った余り": "WARIAMARI", "の要素数": "NO_YOUSOSU",
    "追加する": "TSUIKA_S", "追加し": "TSUIKA_R", "取り出す": "TORIDASU_S", "取り出し": "TORIDASU_R",
    "名付ける": "NAZUKE_S", "名付け": "NAZUKE_R", "生成し": "SEISEI_R", "用意し": "YOUI_R",
    "はい": "HAI", "いいえ": "IIE", "なし": "NASHI", "空": "SORA", "空の配列": "SORA_HAIRETSU",
    "自分": "JIBUN", "自分自身": "JIBUN_JISHIN", "現在の番号": "GENZAI", "その": "SONO",
    "（": "LP", "）": "RP"
  };
  // エラー表示用: 記号名 → 日本語の言葉
  var WORD = { NAME: "名前", NUMBER: "数", STRING: "「文字列」", EOF: "文章の終わり", "$end": "文章の終わり" };
  Object.keys(KW).forEach(function (k) { var v = KW[k]; WORD[v] = WORD[v] ? WORD[v] + "／" + k : k; });

  function strip(src) {
    var chars = [], lines = [], instr = false;
    src.split("\n").forEach(function (line, i) {
      if (/^\s*■/.test(line)) return;
      line = line.split("※")[0];
      for (var c of line) {
        if (c === "「") instr = true; else if (c === "」") instr = false;
        if (instr || !/\s/.test(c)) { chars.push(c); lines.push(i + 1); }   // 「…」の中の空白は残す
      }
    });
    return { t: chars.join(""), lines: lines, cps: chars };
  }
  function findAll(re, t) { var r = [], m; re.lastIndex = 0; while ((m = re.exec(t))) r.push(m[1]); return r; }
  function declaredNames(t) {
    var s = new Set();
    findAll(/([^。、]+?)というアクターを定義する/g, t).forEach(function (n) { s.add(n); });
    findAll(/[^。、]+?は([^。]+?)を持つ。/g, t).forEach(function (d) { d.split("と").forEach(function (n) { s.add(n); }); });
    findAll(/というメッセージと([^。、]+?)を受け取ったとき/g, t).forEach(function (n) { s.add(n); });
    findAll(/、([^、。]+?)と名付け/g, t).forEach(function (n) { s.add(n); });
    findAll(/の先頭から([^、。]+?)を取り出/g, t).forEach(function (n) { s.add(n); });
    return s;
  }
  function lex(src) {
    var st = strip(src), cps = st.cps, names = declaredNames(st.t);
    var table = Object.keys(KW).map(function (k) { return [Array.from(k), KW[k]]; })
      .concat(Array.from(names).map(function (n) { return [Array.from(n), "NAME"]; }));
    table.sort(function (a, b) { return b[0].length - a[0].length; });
    var at = function (i, w) { for (var j = 0; j < w.length; j++) if (cps[i + j] !== w[j]) return false; return true; };
    var out = [], i = 0;
    while (i < cps.length) {
      if (cps[i] === "「") {
        var j = cps.indexOf("」", i);
        if (j < 0) throw new KotoError("字句エラー", st.lines[i], "「 が閉じていない");
        out.push(["STRING", cps.slice(i, j + 1).join(""), st.lines[i]]); i = j + 1; continue;
      }
      var best = null;
      for (var k = 0; k < table.length; k++) if (at(i, table[k][0])) { best = table[k]; break; }
      var m = /^[0-9]+/.exec(cps.slice(i, i + 20).join(""));
      if (m && (!best || m[0].length > best[0].length)) { out.push(["NUMBER", m[0], st.lines[i]]); i += m[0].length; continue; }
      if (!best) throw new KotoError("字句エラー", st.lines[i], "「" + cps.slice(i, i + 12).join("") + "…」は予約語でも宣言された名前でもない");
      out.push([best[1], best[0].join(""), st.lines[i]]); i += best[0].length;
    }
    return out;
  }

  function KotoError(kind, line, msg) { this.kind = kind; this.line = line; this.message = kind + " " + line + "行: " + msg; }

  /* ───── 解析器の動作が呼ぶ補助（kotonoha.y の C 関数と同じ働き） ───── */
  var SEP = "\x1f", NULL = null;
  function cat(n) { return Array.prototype.slice.call(arguments, 1, n + 1).join(""); }
  function ind(s) { return s.replace(/^(?!$)/gm, "    "); }
  function join(s, sep) { return s.split(SEP).filter(function (x) { return x; }).join(sep); }
  function initlines(names, v) { return names.split(SEP).filter(Boolean).map(function (q) { return q + " は " + v + "。\n"; }).join(""); }
  function bnd(s) {
    if (/^\d+$/.test(s)) return s;
    return s.charAt(0) === "（" && closeAt(s, 0) === s.length - 1 ? s : "（" + s + "）";
  }
  function mkitem(kind, actor, h, s) { return { kind: kind, h: h, s: s, next: null }; }
  function append(a, b) { if (!a) return b; var p = a; while (p.next) p = p.next; p.next = b; return a; }
  function print_def(name, decl, items, endname) {
    var init = "", body = "", cur = null, it;
    if (name !== endname) throw new KotoError("意味エラー", 0, "「" + name + "」の定義を「" + endname + "」で閉じている");
    for (it = items; it; it = it.next) {
      if (it.kind === 0) { if (cur || body) throw new KotoError("意味エラー", 0, name + " の初期値の文は受信節より前に書く"); init += it.s; }
      else if (it.kind === 1) { if (cur) body += cur + "以上。\n"; cur = it.h + "\n" + ind(it.s); }
      else { if (!cur) throw new KotoError("意味エラー", 0, name + " で受信節の外に文がある"); cur += ind(it.s); }
    }
    if (cur) body += cur + "以上。\n";
    var inn = init ? "初期状態は\n" + ind(init) + "以上。\n" : "";
    return "「" + name + "」というアクターを定義する。\n" + ind("状態は " + join(decl, "、") + "。\n") + ind(inn) + ind(body) + "定義を終わる。\n";
  }
  var output = null;

  // jison の生成した動作コードは上の名前（cat, ind, SEP, output …）を自由変数として参照する。
  // 生成コードをこの関数の中に埋め込むので、ここで見える。
  /*@@PARSER@@*/

  function toKozo(src) {
    var toks = lex(src), pos = 0, last = null;
    var lexer = {
      setInput: function () { pos = 0; }, yytext: "", yylineno: 0, yylloc: {}, yyleng: 0,
      options: {}, showPosition: function () { return ""; },
      lex: function () {
        if (pos >= toks.length) { this.yytext = ""; last = null; return 1; }
        last = toks[pos++]; this.yytext = last[1]; this.yylineno = last[2]; this.yyleng = last[1].length; return last[0];
      }
    };
    var p = new kotonoha_parser.Parser();
    p.lexer = lexer;
    p.yy.parseError = function (str, hash) {
      var exp = (hash.expected || []).map(function (e) { e = e.replace(/'/g, ""); return WORD[e] || e; });
      var got = last ? "「" + last[1] + "」" : "文章の終わり";
      throw new KotoError("構文エラー", last ? last[2] : 0, got + " の所で止まった。ここに来られるのは: " + exp.join("、"));
    };
    output = null;
    p.parse("");
    return output;
  }

  /* ───── 逆変換（to_bunsho.py の写し） ───── */
  function Lines(text) {
    this.ls = []; var self = this;
    text.split("\n").forEach(function (l, i) { if (l.trim()) self.ls.push([i + 1, l.trim()]); });
    this.i = 0;
  }
  Lines.prototype.peek = function () { return this.i < this.ls.length ? this.ls[this.i][1] : null; };
  Lines.prototype.next = function () {
    if (this.i >= this.ls.length) throw new KotoError("逆変換エラー", this.ls.length, "途中で終わっている");
    return this.ls[this.i++];
  };
  Lines.prototype.expect = function (s) { var nl = this.next(); if (nl[1] !== s) throw new KotoError("逆変換エラー", nl[0], "「" + s + "」のはずが「" + nl[1] + "」"); };
  function fm(re, s) { return new RegExp("^(?:" + re.source + ")$").exec(s); }

  function parseProgram(L) {
    var defs = [];
    while (L.peek() && /というアクターを定義する。$/.test(L.peek())) defs.push(parseDef(L));
    var ms = L.peek() !== null ? L.ls[L.i][0] : 0;
    L.expect("実行を始める。");
    var body = parseBlock(L, ["実行を終わる。"]);
    var me = L.peek() !== null ? L.ls[L.i][0] : 0;
    L.expect("実行を終わる。");
    body.line = ms; body.end = me;
    return [defs, body];
  }
  function parseDef(L) {
    var nl = L.next(), m = fm(/「(.+?)」というアクターを定義する。/, nl[1]), dline = nl[0];
    if (!m) throw new KotoError("逆変換エラー", nl[0], "アクター定義のはずが「" + nl[1] + "」");
    var name = m[1];
    nl = L.next(); m = fm(/状態は (.+)。/, nl[1]);
    if (!m) throw new KotoError("逆変換エラー", nl[0], "「状態は …。」のはずが「" + nl[1] + "」");
    var fields = m[1].split("、"), inits = [], handlers = [];
    if (L.peek() === "初期状態は") {
      L.next();
      while (L.peek() !== "以上。") {
        nl = L.next(); m = fm(/(\S+) は (.+)。/, nl[1]);
        if (!m) throw new KotoError("逆変換エラー", nl[0], "初期値のはずが「" + nl[1] + "」");
        inits.push([m[1], m[2]]);
      }
      L.next();
    }
    while (L.peek() !== "定義を終わる。") {
      nl = L.next(); m = fm(/「(.+?)」(?:と (\S+) )?を受け取ったとき、/, nl[1]);
      if (!m) throw new KotoError("逆変換エラー", nl[0], "受信節の頭のはずが「" + nl[1] + "」");
      var scope = new Set(fields); if (m[2]) scope.add(m[2]);
      var body = parseBlock(L, ["以上。"], scope), hline = nl[0];
      nl = L.next(); if (nl[1] !== "以上。") throw new KotoError("逆変換エラー", nl[0], "「以上。」のはずが「" + nl[1] + "」");
      var hh = [m[1], m[2] || null, body]; hh.line = hline; hh.end = nl[0]; handlers.push(hh);
    }
    var dend = L.next();
    var dd = [name, fields, inits, handlers]; dd.line = dline; dd.end = dend[0]; return dd;
  }
  function parseBlock(L, enders, scope) {
    scope = scope || new Set();
    var out = [];
    while (enders.indexOf(L.peek()) < 0 && L.peek() !== "そうでなければ、") {
      if (L.peek() === null) throw new KotoError("逆変換エラー", L.ls.length, "「" + enders[0] + "」が無いまま終わっている");
      out.push(parseStmt(L, scope));
    }
    return out;
  }
  var PATS = [
    [/(.+) を表示する。/, "disp"],
    [/(.+) の全員に(「.+?」)(?:と (.+) )?を送る。/, "zenin"],
    [/(.+) に それぞれ(「.+?」)(?:と (.+) )?を送る。/, "each"],
    [/(.+) に(「.+?」)(?:と (.+) )?を送る。/, "send"],
    [/(.+) に (.+) を追加する。/, "push"],
    [/(\S+) は (.+) の先頭を取り出す。/, "take"],
    [/(\S+) は 「(.+?)」の新しいアクター。/, "new"],
    [/(\S+?の .+? 番目) は (.+)。/, "chg"],
    [/(\S+) は (\S+) 足す (.+)。/, "add"],
    [/(\S+) は (.+)。/, "chg"]
  ];
  function parseStmt(L, scope) {
    var nl = L.next(), l = nl[1], m = fm(/もし (.+?) が (.+?)( でない| より小さい)? ならば、/, l);
    if (m) {
      var kind = { undefined: "ならば", " でない": "でなければ", " より小さい": "より小さければ" }[m[3]];
      var then = parseBlock(L, ["以上。"], scope), els = null;
      if (L.peek() === "そうでなければ、") { L.next(); els = parseBlock(L, ["以上。"], scope); }
      var endl = L.next(); if (endl[1] !== "以上。") throw new KotoError("逆変換エラー", endl[0], "「以上。」のはずが「" + endl[1] + "」");
      var r = ["if", [m[1], m[2], kind], then, els]; r.line = nl[0]; r.end = endl[0]; return r;
    }
    m = fm(/(.+?)から(.+)まで繰り返す。/, l);
    if (m) { var b = parseBlock(L, ["以上。"], scope); L.expect("以上。"); var r2 = ["loop", m[1], m[2], b]; r2.line = nl[0]; return r2; }
    for (var i = 0; i < PATS.length; i++) {
      m = fm(PATS[i][0], l); if (!m) continue;
      var k = PATS[i][1], g = m.slice(1).map(function (x) { return x === undefined ? null : x; });
      if (k === "add" && g[0] !== g[1]) continue;
      if (k === "chg" && g[1] === "空の配列" && !scope.has(g[0])) k = "array";
      if (k === "take" || k === "new" || k === "array") scope.add(g[0]);
      var r3 = [k].concat(g); r3.line = nl[0]; return r3;
    }
    throw new KotoError("逆変換エラー", nl[0], "読めない文「" + l + "」");
  }

  // 括弧の対応と、括弧の外の区切りを探す（式は文字列のまま持っているので）
  function closeAt(e, i) {
    for (var d = 0, j = i; j < e.length; j++) {
      if (e[j] === "（") d++;
      else if (e[j] === "）" && --d === 0) return j;
    }
    return -1;
  }
  function top(s, sep) {
    for (var d = 0, j = 0; j < s.length; j++) {
      if (s[j] === "（") d++; else if (s[j] === "）") d--;
      else if (d === 0 && s.startsWith(sep, j)) return j;
    }
    return -1;
  }
  function arith(e) {     // 全体が（…）なら [種類, A, B]（add/sub/mod）、ただの括弧は ["paren", X]
    if (!(e.charAt(0) === "（" && closeAt(e, 0) === e.length - 1)) return null;
    var s = e.slice(1, -1).trim(), seps = [[" 足す ", "add"], [" 引く ", "sub"]];
    for (var i = 0; i < seps.length; i++) {
      var j = top(s, seps[i][0]);
      if (j >= 0) return [seps[i][1], s.slice(0, j), s.slice(j + seps[i][0].length)];
    }
    if (/ で割った余り$/.test(s)) { var k = top(s, " を "); if (k >= 0) return ["mod", s.slice(0, k), s.slice(k + 3, -" で割った余り".length)]; }
    return ["paren", s];
  }
  function expr(e) {
    e = e.trim();
    if (e === "自分") return "自分自身";
    var a = arith(e);
    if (a) {
      if (a[0] === "add") return "（" + expr(a[1]) + "に" + expr(a[2]) + "を加えた数）";
      if (a[0] === "sub") return "（" + expr(a[1]) + "から" + expr(a[2]) + "を引いた数）";
      if (a[0] === "mod") return "（" + expr(a[1]) + "を" + expr(a[2]) + "で割った余り）";
      return expr(a[1]);
    }
    if (/ の要素数$/.test(e)) return expr(e.slice(0, -" の要素数".length)) + "の要素数";
    var m = fm(/(.+?)の (.+) 番目/, e);
    if (m) {
      var idx = m[2].trim(), ai = arith(idx);
      if (/^\d+$/.test(idx)) ;
      else if (ai && ai[0] !== "paren") idx = expr(idx);
      else idx = "（" + expr(idx) + "）";
      return expr(m[1]) + "の" + idx + "番目";
    }
    return e;
  }
  function exprs(s, strings) {
    return s.split(" と ").map(function (p) { return expr(p) + (strings && p.charAt(0) === "「" ? "という文字列" : ""); }).join("と");
  }
  function clause(st, fin) {
    var k = st[0], g = st.slice(1), V = function (s, r) { return fin ? s : r; };
    var arg = function (a) { return a ? "と" + expr(a) : ""; };
    switch (k) {
      case "disp":  return exprs(g[0], true) + "を" + V("表示する", "表示し");
      case "send":  return exprs(g[0]) + "に" + g[1] + "というメッセージ" + arg(g[2]) + "を" + V("送る", "送り");
      case "each":  return exprs(g[0]) + "にそれぞれ" + g[1] + "というメッセージ" + arg(g[2]) + "を" + V("送る", "送り");
      case "zenin": return expr(g[0]) + "の全員に" + g[1] + "というメッセージ" + arg(g[2]) + "を" + V("送る", "送り");
      case "push":  return exprs(g[1]) + "を" + expr(g[0]) + "の末尾に" + V("追加する", "追加し");
      case "take":  return expr(g[1]) + "の先頭から" + g[0] + "を" + V("取り出す", "取り出し");
      case "new":   return g[1] + "というアクターを1つ生成し、" + g[0] + "と" + V("名付ける", "名付け");
      case "array": return "空の配列を用意し、" + g[0] + "と" + V("名付ける", "名付け");
      case "add":   return expr(g[0]) + "に" + expr(g[2]) + "を" + V("加える", "加え");
      case "chg":   return exprs(g[0]) + "を" + expr(g[1]) + "に" + (g[0].indexOf("の") >= 0 ? V("設定する", "設定し") : V("変更する", "変更し"));
    }
    throw new Error(k);
  }
  var MAXJOIN = 3;
  function simple(st) { return st[0] !== "if" && st[0] !== "loop"; }
  function sentences(stmts) {
    var out = [], run = [];
    function flush() {
      while (run.length) {
        var chunk = run.splice(0, MAXJOIN);
        out.push(chunk.map(function (s, i) { return clause(s, i === chunk.length - 1); }).join("、") + "。");
      }
    }
    stmts.forEach(function (st) { if (simple(st)) run.push(st); else { flush(); out.push.apply(out, compound(st)); } });
    flush();
    return out;
  }
  function part(stmts) {
    if (stmts.length > 0 && stmts.length <= MAXJOIN && stmts.every(simple)) return [sentences(stmts)[0]];
    return ["次のことを行う。"].concat(sentences(stmts), ["以上。"]);
  }
  function joined(prefix, lines) { return [prefix + lines[0]].concat(lines.slice(1)); }
  function compound(st) {
    if (st[0] === "loop") return joined(expr(st[1]) + "から" + expr(st[2]) + "までの各番号について、", part(st[3]));
    var c = st[1], out = joined(expr(c[0]) + "が" + expr(c[1]) + c[2] + "、", part(st[2]));
    if (st[3] !== null) {
      var e = joined("そうでなければ、", part(st[3]));
      if (out[out.length - 1] === "以上。") out = out.concat(e);
      else { out[out.length - 1] += e[0]; out = out.concat(e.slice(1)); }
    }
    return out;
  }
  function emit(defs, body) {
    var out = [];
    defs.forEach(function (d) {
      var name = d[0], fields = d[1], inits = d[2], handlers = d[3];
      out.push(name + "というアクターを定義する。");
      out.push(name + "は" + fields.join("と") + "を持つ。");
      if (inits.length) {
        var groups = [];
        inits.forEach(function (fv) {
          var last = groups[groups.length - 1];
          if (last && last[1] === fv[1]) last[0].push(fv[0]); else groups.push([[fv[0]], fv[1]]);
        });
        out.push(groups.map(function (g) { return g[0].join("と") + "の初期値は" + expr(g[1]); }).join("とし、") + "とする。");
      }
      handlers.forEach(function (h) {
        out.push("");
        var head = name + "が「" + h[0] + "」というメッセージ" + (h[1] ? "と" + h[1] : "") + "を受け取ったとき、";
        var ss = sentences(h[2]); out = out.concat(joined(head, ss.length ? ss : ["。"]));
      });
      out.push("", "これで" + name + "の定義を終わる。", "");
    });
    out = out.concat(["実行を始める。", ""], sentences(body), ["", "これで実行を終わる。"]);
    return out.join("\n") + "\n";
  }
  function toBunsho(text) { var r = parseProgram(new Lines(text)); return emit(r[0], r[1]); }

  /* ───── 実行系 ─────
   * 構造化形式を parseProgram で構文木にし、それを解釈する。
   *   - アクターは受信箱を一つ持ち、届いたメッセージを一通ずつ処理する（一つのアクターの中は逐次）。
   *   - どのアクターが次に動くかは order で決める: "random"＝種つき乱数（並列の非決定性を再現できる形で見せる）、
   *     "fifo"＝送られた順。
   *   - 「実行を始める。」の部分は、特別な主体（自分を持たない）が上から順に一度だけ実行する。
   */
  function RunError(msg) { this.message = "実行時エラー: " + msg; }
  function mulberry32(a) {
    return function () { a |= 0; a = a + 0x6D2B79F5 | 0; var t = Math.imul(a ^ a >>> 15, 1 | a);
      t = t + Math.imul(t ^ t >>> 7, 61 | t) ^ t; return ((t ^ t >>> 14) >>> 0) / 4294967296; };
  }

  function makeRun(src, opts) {
    opts = opts || {};
    var kozo = toKozo(src);
    var tree = parseProgram(new Lines(kozo)), defs = tree[0], main = tree[1];
    var classes = {}, names = new Set(["自分"]);
    defs.forEach(function (d) {
      var h = {};
      d[3].forEach(function (x) { h[x[0]] = { param: x[1], body: x[2] }; if (x[1]) names.add(x[1]); });
      classes[d[0]] = { name: d[0], fields: d[1], inits: d[2], handlers: h, count: 0 };
      d[1].forEach(function (f) { names.add(f); });
    });
    (function collect(stmts) {
      stmts.forEach(function (st) {
        if (st[0] === "if") { collect(st[2]); if (st[3]) collect(st[3]); }
        else if (st[0] === "loop") collect(st[3]);
        else if (st[0] === "take" || st[0] === "new" || st[0] === "array") names.add(st[1]);
        else if (st[0] === "chg" && st[1].indexOf("の") < 0) st[1].split(" と ").forEach(function (n) { names.add(n.trim()); });
      });
    })(main.concat.apply(main, defs.map(function (d) { return [].concat.apply([], d[3].map(function (x) { return x[2]; })); })));
    var byLen = Array.from(names).sort(function (a, b) { return b.length - a.length; });

    var rand = mulberry32(opts.seed >>> 0 || 1), order = opts.order || "random";
    var ready = [], actors = [], processed = 0, out = [], verbose = !!opts.verbose;
    var emitLine = function (text, kind) { out.push({ text: text, kind: kind || "out" }); };

    function show(v) {
      if (v === null || v === undefined) return "なし";
      if (v === true) return "はい"; if (v === false) return "いいえ";
      if (Array.isArray(v)) return "[" + v.map(show).join("、") + "]";
      if (typeof v === "object" && v.cls) return v.cls.name + "#" + v.id;
      return String(v);
    }
    function splitPath(e) {
      var segs = [], pos = 0;
      while (pos < e.length) {
        var hit = null;
        for (var i = 0; i < byLen.length; i++) {
          var n = byLen[i];
          if (e.startsWith(n, pos) && (pos + n.length === e.length || e.startsWith("の", pos + n.length))) { hit = n; break; }
        }
        if (!hit) throw new RunError("「" + e + "」の「" + e.slice(pos) + "」が読めない（宣言されていない名前）");
        segs.push(hit); pos += hit.length;
        if (pos < e.length) pos += 1;
      }
      return segs;
    }
    function lookup(name, ctx) {
      if (ctx.locals.has(name)) return ctx.locals.get(name);
      if (name === "自分") { if (!ctx.self) throw new RunError("「実行を始める。」の中に自分は無い"); return ctx.self; }
      if (ctx.self && ctx.self.cls.fields.indexOf(name) >= 0) return ctx.self.state[name];
      throw new RunError("「" + name + "」に値が入っていない");
    }
    function field(obj, f, whole) {
      if (!obj || !obj.cls) throw new RunError("「" + whole + "」: " + show(obj) + " はアクターではないので「" + f + "」を持たない");
      if (obj.cls.fields.indexOf(f) < 0) throw new RunError("「" + whole + "」: " + obj.cls.name + " は「" + f + "」を持たない");
      return obj;
    }
    function ev(e, ctx) {
      e = e.trim();
      var m;
      if (/^\d+$/.test(e)) return Number(e);
      if ((m = /^「(.*)」$/.exec(e))) return m[1];
      if (e === "はい") return true; if (e === "いいえ") return false; if (e === "なし") return null;
      if (e === "空" || e === "空の配列") return [];
      if (e === "現在の番号") { if (!ctx.loop.length) throw new RunError("繰り返しの外で「現在の番号」を使った"); return ctx.loop[ctx.loop.length - 1]; }
      var a = arith(e);
      if (a) {
        if (a[0] === "paren") return ev(a[1], ctx);
        var x = num(ev(a[1], ctx), e), y = num(ev(a[2], ctx), e);
        if (a[0] === "add") return x + y;
        if (a[0] === "sub") return x - y;
        if (y === 0) throw new RunError("「" + e + "」: 0 で割ろうとした");
        return ((x % y) + y) % y;
      }
      if (/ の要素数$/.test(e)) {
        var arr = ev(e.slice(0, -" の要素数".length), ctx);
        if (!Array.isArray(arr)) throw new RunError("「" + e + "」: " + show(arr) + " は配列ではないので要素数が無い");
        return arr.length;
      }
      if ((m = /^(.+?)の (.+) 番目$/.exec(e))) { var el = elem(m, e, ctx); return el.arr[el.k - 1]; }
      var segs = splitPath(e), v = lookup(segs[0], ctx);
      for (var i = 1; i < segs.length; i++) v = field(v, segs[i], e).state[segs[i]];
      return v;
    }
    function elem(m, e, ctx) {      // 「X の i 番目」の X と i を求めて範囲を確かめる
      var base = ev(m[1], ctx), k = num(ev(m[2], ctx), e);
      if (!Array.isArray(base)) throw new RunError("「" + e + "」: " + show(base) + " は配列ではない");
      if (k < 1 || k > base.length) throw new RunError("「" + e + "」: " + k + " 番目は無い（" + base.length + " 個しかない）");
      return { arr: base, k: k };
    }
    function num(v, e) { if (typeof v !== "number") throw new RunError("「" + e + "」: " + show(v) + " は数ではない"); return v; }
    function assign(target, val, ctx) {
      var m = /^(.+?)の (.+) 番目$/.exec(target.trim());
      if (m) { var el = elem(m, target.trim(), ctx); el.arr[el.k - 1] = val; return; }
      var segs = splitPath(target.trim());
      if (segs.length === 1) {
        var n = segs[0];
        if (!ctx.locals.has(n) && ctx.self && ctx.self.cls.fields.indexOf(n) >= 0) ctx.self.state[n] = val;
        else ctx.locals.set(n, val);
        return;
      }
      var obj = lookup(segs[0], ctx);
      for (var i = 1; i < segs.length - 1; i++) obj = field(obj, segs[i], target).state[segs[i]];
      field(obj, segs[segs.length - 1], target).state[segs[segs.length - 1]] = val;
    }
    function eq(a, b) {
      if (Array.isArray(a) && Array.isArray(b)) return a.length === 0 && b.length === 0 || a === b;
      return a === b;
    }
    function newActor(cname) {
      var c = classes[cname];
      if (!c) throw new RunError("「" + cname + "」というアクターは定義されていない");
      var a = { cls: c, id: ++c.count, state: {}, box: [] };
      c.fields.forEach(function (f) { a.state[f] = null; });
      var ctx = { self: a, locals: new Map(), loop: [] };
      c.inits.forEach(function (fv) { a.state[fv[0]] = ev(fv[1], ctx); });
      actors.push(a);
      if (verbose) emitLine("＋ " + show(a) + " を生成", "trace");
      return a;
    }
    function send(target, msg, arg, ctx) {
      if (!target || !target.cls) throw new RunError(show(target) + " はアクターではないので「" + msg + "」を送れない");
      target.box.push({ msg: msg, arg: arg, from: ctx.self });
      ready.push(target);
      if (verbose) emitLine("→ " + (ctx.self ? show(ctx.self) : "実行部") + " から " + show(target) + " へ「" + msg + "」" + (arg !== undefined ? "（" + show(arg) + "）" : ""), "trace");
    }
    function list(s) { return s.split(" と "); }
    function exec(stmts, ctx) {
      for (var i = 0; i < stmts.length; i++) {
        var st = stmts[i], k = st[0], g = st.slice(1);
        if (k === "if") {
          var a = ev(g[0][0], ctx), b = ev(g[0][1], ctx), c;
          if (g[0][2] === "ならば") c = eq(a, b);
          else if (g[0][2] === "でなければ") c = !eq(a, b);
          else c = num(a, g[0][0]) < num(b, g[0][1]);
          if (c) exec(g[1], ctx); else if (g[2]) exec(g[2], ctx);
        } else if (k === "loop") {
          var lo = num(ev(g[0], ctx), g[0]), hi = num(ev(g[1], ctx), g[1]);   // 範囲は入る前に一度だけ計算
          for (var n = lo; n <= hi; n++) { ctx.loop.push(n); exec(g[2], ctx); ctx.loop.pop(); }
        } else if (k === "disp") {
          // 並べて表示: 値と値が隣り合うときだけ空白を入れる（「…」の文字列の前後には入れない）
          var parts = list(g[0]).map(function (x) { return { lit: x.trim().charAt(0) === "「", v: show(ev(x, ctx)) }; }), s = "";
          parts.forEach(function (p, j) { s += (j && !p.lit && !parts[j - 1].lit ? " " : "") + p.v; });
          emitLine(s, "out");
        } else if (k === "send" || k === "each" || k === "zenin") {
          var msg = g[1].slice(1, -1), arg = g[2] ? ev(g[2], ctx) : undefined;
          var targets = k === "zenin" ? ev(g[0], ctx) : list(g[0]).map(function (x) { return ev(x, ctx); });
          if (!Array.isArray(targets)) throw new RunError("「" + g[0] + "」は配列ではないので全員に送れない");
          targets.forEach(function (t) { send(t, msg, arg, ctx); });
        } else if (k === "push") {
          var arr = ev(g[0], ctx);
          if (!Array.isArray(arr)) throw new RunError("「" + g[0] + "」は配列ではないので追加できない");
          list(g[1]).forEach(function (x) { arr.push(ev(x, ctx)); });
        } else if (k === "take") {
          var q = ev(g[1], ctx);
          if (!Array.isArray(q)) throw new RunError("「" + g[1] + "」は配列ではない");
          if (!q.length) throw new RunError("「" + g[1] + "」が空なので先頭を取り出せない");
          assign(g[0], q.shift(), ctx);
        } else if (k === "new") assign(g[0], newActor(g[1]), ctx);
        else if (k === "array") assign(g[0], [], ctx);
        else if (k === "add") assign(g[0], num(ev(g[0], ctx), g[0]) + num(ev(g[2], ctx), g[2]), ctx);
        else if (k === "chg") { var v = ev(g[1], ctx); list(g[0]).forEach(function (t) { assign(t, v, ctx); }); }
        else throw new RunError("知らない文 " + k);
      }
    }

    var state = { done: false, error: null, stoppedByLimit: false };
    try { exec(main, { self: null, locals: new Map(), loop: [] }); }
    catch (e) { state.done = true; state.error = e.message || String(e); }

    function step(maxMsgs) {
      var n = 0;
      try {
        while (!state.done && ready.length && n < maxMsgs) {
          var idx = order === "fifo" ? 0 : Math.floor(rand() * ready.length);
          var a = ready.splice(idx, 1)[0], m = a.box.shift(), h = a.cls.handlers[m.msg];
          processed++; n++;
          if (verbose) emitLine("◇ " + show(a) + " が「" + m.msg + "」を処理", "trace");
          if (!h) throw new RunError(show(a) + " は「" + m.msg + "」を受け取る受信節を持たない");
          var locals = new Map(); if (h.param) locals.set(h.param, m.arg);
          exec(h.body, { self: a, locals: locals, loop: [] });
          if (opts.limit && processed >= opts.limit) { state.done = true; state.stoppedByLimit = true; }
        }
        if (!ready.length) state.done = true;
      } catch (e) { state.done = true; state.error = e.message || String(e); }
      var lines = out; out = [];
      return { lines: lines, done: state.done, error: state.error, stoppedByLimit: state.stoppedByLimit, processed: processed };
    }
    // 止まったあとで、状態の中の配列（アクターだけが並ぶもの）にアクターが残っていれば「待たされている」と報告する
    function waiting() {
      var r = [];
      actors.forEach(function (a) {
        a.cls.fields.forEach(function (f) {
          var v = a.state[f];
          // 待ち行列＝アクターだけが並ぶ配列。数や文字列が混じる配列（依頼の組など）はただのデータなので数えない
          if (Array.isArray(v) && v.length && v.every(function (x) { return x && x.cls; }))
            r.push(show(a) + " の「" + f + "」で " + v.map(show).join("、") + " が待っている");
        });
      });
      return r;
    }
    return { kozo: kozo, step: step, waiting: waiting, actors: function () { return actors.length; } };
  }

  return { toKozo: toKozo, toBunsho: toBunsho, lex: lex, makeRun: makeRun, KotoError: KotoError,
    // Xinu 向け変換器（../xinu/k2xinu.mjs）が構文木と式の分解を使う
    _tree: function (src) { return parseProgram(new Lines(toKozo(src))); }, _arith: arith,
    // 流れ図のページ（site/flow.js）が文を文章形式の言い回しに戻すのに使う
    _clause: clause, _expr: expr };
})();
if (typeof module !== "undefined") module.exports = Kotonoha;
