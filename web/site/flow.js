/* 流れ図のページ: ことのはの文章形式 → 構文木（Kotonoha._tree）→ 受信節ごとの流れ図（SVG）
 *   記号は JIS X 0121 に沿う: 端子・処理・判断・ループ端・表示。メッセージの送信だけはこの図で決めた記号（右が尖った五角形）。
 *   配置は構造をそのまま積む: 文は縦に並べ、条件は「はい」を下、「いいえ」を右に出して下で合流させる。
 */
(function () {
  "use strict";
  var K = Kotonoha;
  var FS = 13, LH = 18, PX = 12, PY = 9, GAP = 26, MAXW = 230, DMAXW = 150, MARGIN = 24;
  var C = { line: "#5f6b80", ink: "#1d2433", term: "#f6e9e6", termS: "#7a2e3a", proc: "#ffffff", procS: "#8a93a6",
            dec: "#fff7e6", decS: "#c8553d", loop: "#eef4fb", loopS: "#3a6ea5", send: "#eaf5ea", sendS: "#2e7d32",
            disp: "#f3effa", dispS: "#6a4c9c", lab: "#c8553d" };

  function cw(c) { return c.charCodeAt(0) < 0x80 ? FS * 0.6 : FS; }
  function tw(s) { var w = 0; for (var c of s) w += cw(c); return w; }
  var NOHEAD = "、。」）』ー";
  function wrap(s, maxw) {
    var out = [], cur = "", w = 0;
    for (var c of s) {
      if (w + cw(c) > maxw && cur && NOHEAD.indexOf(c) < 0) { out.push(cur); cur = ""; w = 0; }
      cur += c; w += cw(c);
    }
    if (cur) out.push(cur);
    return out.length ? out : [""];
  }
  function esc(s) { return String(s).replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;").replace(/"/g, "&quot;"); }
  function texts(lines, cx, cy) {
    var y0 = cy - (lines.length - 1) * LH / 2;
    return lines.map(function (l, i) {
      return '<text x="' + cx + '" y="' + (y0 + i * LH) + '" text-anchor="middle" dominant-baseline="central">' + esc(l) + "</text>";
    }).join("");
  }
  function arrow(x1, y1, x2, y2) { return '<path d="M' + x1 + " " + y1 + " L" + x2 + " " + y2 + '" class="e" marker-end="url(#ah)"/>'; }
  function path(d, mark) { return '<path d="' + d + '" class="e"' + (mark ? ' marker-end="url(#ah)"' : "") + "/>"; }

  /* 各部品は { l, r, h, draw(cx, y) }。l/r は中心線から左右へのはみ出し */
  function shape(kind, text, title) {
    var lines = wrap(text, MAXW), w = Math.max.apply(null, lines.map(tw)), h = lines.length * LH + PY * 2;
    var extra = { send: 16, disp: 22, term: h / 2, loopT: 10, loopB: 10 }[kind] || 0;
    var W = Math.max(w + PX * 2 + extra, kind === "term" ? 120 : 90), hw = W / 2;
    return { l: hw, r: hw, h: h, draw: function (cx, y) {
      var x0 = cx - hw, x1 = cx + hw, y1 = y + h, d, f, s;
      switch (kind) {
        case "term": f = C.term; s = C.termS;
          d = '<rect x="' + x0 + '" y="' + y + '" width="' + W + '" height="' + h + '" rx="' + h / 2 + '"'; break;
        case "send": f = C.send; s = C.sendS;
          d = '<path d="M' + x0 + " " + y + " L" + (x1 - 14) + " " + y + " L" + x1 + " " + (y + h / 2) + " L" + (x1 - 14) + " " + y1 + " L" + x0 + " " + y1 + ' Z"'; break;
        case "disp": f = C.disp; s = C.dispS;
          d = '<path d="M' + (x0 + 16) + " " + y + " L" + (x1 - 14) + " " + y + " Q" + (x1 + 6) + " " + (y + h / 2) + " " + (x1 - 14) + " " + y1 +
              " L" + (x0 + 16) + " " + y1 + " L" + x0 + " " + (y + h / 2) + ' Z"'; break;
        case "loopT": f = C.loop; s = C.loopS;
          d = '<path d="M' + (x0 + 10) + " " + y + " L" + (x1 - 10) + " " + y + " L" + x1 + " " + (y + 10) + " L" + x1 + " " + y1 +
              " L" + x0 + " " + y1 + " L" + x0 + " " + (y + 10) + ' Z"'; break;
        case "loopB": f = C.loop; s = C.loopS;
          d = '<path d="M' + x0 + " " + y + " L" + x1 + " " + y + " L" + x1 + " " + (y1 - 10) + " L" + (x1 - 10) + " " + y1 +
              " L" + (x0 + 10) + " " + y1 + " L" + x0 + " " + (y1 - 10) + ' Z"'; break;
        default: f = C.proc; s = C.procS;
          d = '<rect x="' + x0 + '" y="' + y + '" width="' + W + '" height="' + h + '"';
      }
      return "<g>" + (title ? "<title>" + esc(title) + "</title>" : "") + d + ' fill="' + f + '" stroke="' + s + '" stroke-width="1.4"/>' +
        texts(lines, cx + (kind === "send" ? -5 : kind === "disp" ? 2 : 0), y + h / 2) + "</g>";
    } };
  }
  var EMPTY = { l: 0, r: 0, h: 0, draw: function () { return ""; } };

  function seq(parts) {
    parts = parts.filter(function (p) { return p.h > 0; });
    if (!parts.length) return EMPTY;
    var h = 0, l = 0, r = 0;
    parts.forEach(function (p, i) { h += p.h + (i ? GAP : 0); l = Math.max(l, p.l); r = Math.max(r, p.r); });
    return { l: l, r: r, h: h, draw: function (cx, y) {
      var s = "";
      parts.forEach(function (p, i) {
        if (i) { s += arrow(cx, y, cx, y + GAP); y += GAP; }
        s += p.draw(cx, y); y += p.h;
      });
      return s;
    } };
  }

  function decision(text, T, E) {
    var lines = wrap(text, DMAXW), a = Math.max.apply(null, lines.map(tw)) / 2 + 6, b = lines.length * LH / 2 + 2;
    var B = b + 16, A = Math.max(a * B / (B - b), 70);
    var off = Math.max(A, T.r) + 34 + E.l, hasE = E.h > 0;
    var bodyH = Math.max(T.h, E.h), h = 2 * B + GAP + bodyH + 16;
    return { l: Math.max(A, T.l), r: off + Math.max(E.r, 10), h: h, draw: function (cx, y) {
      var s = '<path d="M' + cx + " " + y + " L" + (cx + A) + " " + (y + B) + " L" + cx + " " + (y + 2 * B) + " L" + (cx - A) + " " + (y + B) +
              ' Z" fill="' + C.dec + '" stroke="' + C.decS + '" stroke-width="1.4"/>' + texts(lines, cx, y + B);
      var top = y + 2 * B + GAP, mergeY = top + bodyH + 16, ex = cx + off;
      s += '<text x="' + (cx + 6) + '" y="' + (y + 2 * B + 12) + '" class="lab">はい</text>';
      s += '<text x="' + (cx + A + 6) + '" y="' + (y + B - 7) + '" class="lab">いいえ</text>';
      if (T.h) { s += arrow(cx, y + 2 * B, cx, top) + T.draw(cx, top) + path("M" + cx + " " + (top + T.h) + " L" + cx + " " + mergeY); }
      else s += path("M" + cx + " " + (y + 2 * B) + " L" + cx + " " + mergeY);
      if (hasE) {
        s += path("M" + (cx + A) + " " + (y + B) + " L" + ex + " " + (y + B) + " L" + ex + " " + top, true) + E.draw(ex, top);
        s += path("M" + ex + " " + (top + E.h) + " L" + ex + " " + mergeY + " L" + (cx + 3) + " " + mergeY, true);
      } else {
        s += path("M" + (cx + A) + " " + (y + B) + " L" + ex + " " + (y + B) + " L" + ex + " " + mergeY + " L" + (cx + 3) + " " + mergeY, true);
      }
      return s + '<circle cx="' + cx + '" cy="' + mergeY + '" r="2.5" fill="' + C.line + '"/>';
    } };
  }

  /* 構文木 → 部品 */
  function condText(c) {
    var a = K._expr(c[0]), b = K._expr(c[1]);
    return c[2] === "ならば" ? a + "が" + b + "か？" : c[2] === "でなければ" ? a + "が" + b + "でないか？" : a + "が" + b + "より小さいか？";
  }
  function build(stmts, ctx) {
    return seq(stmts.map(function (st) {
      if (st[0] === "if") return decision(condText(st[1]), build(st[2], ctx), st[3] ? build(st[3], ctx) : EMPTY);
      if (st[0] === "loop") {
        var n = ++ctx.loops;
        return seq([shape("loopT", "繰り返し" + n + "：" + K._expr(st[1]) + "から" + K._expr(st[2]) + "までの各番号"),
                    build(st[3], ctx), shape("loopB", "繰り返し" + n)]);
      }
      var kind = { send: "send", each: "send", zenin: "send", disp: "disp" }[st[0]] || "proc";
      var t = K._clause(st, true);
      return shape(kind, t, t + "。");
    }));
  }
  function chart(startText, endText, stmts) {
    var body = seq([shape("term", startText), build(stmts, { loops: 0 }), shape("term", endText)]);
    var W = Math.ceil(body.l + body.r + MARGIN * 2), H = Math.ceil(body.h + MARGIN * 2), cx = MARGIN + body.l;
    return '<svg xmlns="http://www.w3.org/2000/svg" width="' + W + '" height="' + H + '" viewBox="0 0 ' + W + " " + H + '">' +
      "<defs><marker id=\"ah\" viewBox=\"0 0 10 10\" refX=\"9\" refY=\"5\" markerWidth=\"7\" markerHeight=\"7\" orient=\"auto-start-reverse\">" +
      '<path d="M0 0 L10 5 L0 10 z" fill="' + C.line + '"/></marker>' +
      "<style>text{font-family:'Hiragino Kaku Gothic ProN','Noto Sans JP',Meiryo,sans-serif;font-size:" + FS + "px;fill:" + C.ink + "}" +
      ".e{fill:none;stroke:" + C.line + ";stroke-width:1.4}.lab{font-size:11px;fill:" + C.lab + ";font-weight:700}</style></defs>" +
      '<rect width="100%" height="100%" fill="#fff"/>' + body.draw(cx, MARGIN) + "</svg>";
  }

  /* ───── 画面 ───── */
  var $ = function (id) { return document.getElementById(id); };
  var src = $("src"), out = $("charts"), status = $("status"), sel = $("sample"), toc = $("toc");
  function show(ok, msg) { status.className = "status " + (ok ? "ok" : "err"); status.textContent = msg; }
  function card(id, title, sub, svg, fname) {
    return '<div class="chart" id="' + id + '"><div class="chart-h"><b>' + esc(title) + "</b>" + (sub ? '<span class="sub">' + esc(sub) + "</span>" : "") +
      '<button class="btn light dl" type="button" data-f="' + esc(fname) + '">SVG で保存</button></div><div class="svgwrap">' + svg + "</div></div>";
  }
  function render() {
    var tree;
    try { tree = K._tree(src.value); }
    catch (e) { show(false, "✗ " + (e.message || e)); return; }
    var defs = tree[0], main = tree[1], html = "", links = [], n = 0, count = 0;
    defs.forEach(function (d) {
      var name = d[0], fields = d[1], inits = d[2], handlers = d[3];
      var initText = inits.map(function (fv) { return fv[0] + "＝" + K._expr(fv[1]); }).join("、");
      html += '<div class="actor" id="a' + (++n) + '"><div class="actor-h"><span class="tag">アクター</span><b>' + esc(name) + "</b></div>" +
        '<div class="actor-s">状態：' + esc(fields.join("、")) + (initText ? "　／　初期値：" + esc(initText) : "") + "</div>";
      links.push('<a href="#a' + n + '" class="chip a">' + esc(name) + "</a>");
      handlers.forEach(function (h) {
        var id = "c" + (++n), head = name + "が「" + h[0] + "」" + (h[1] ? "と" + h[1] : "") + "を受け取ったとき";
        html += card(id, "「" + h[0] + "」を受け取ったとき", h[1] ? "受け取る値：" + h[1] : "", chart(head, "次のメッセージを待つ", h[2]), name + "_" + h[0] + ".svg");
        links.push('<a href="#' + id + '" class="chip">' + esc(name) + "：「" + esc(h[0]) + "」</a>");
        count++;
      });
      if (!handlers.length) html += '<p class="none">受信節がありません（状態を持つだけのアクター）。</p>';
      html += "</div>";
    });
    html += '<div class="actor" id="cmain"><div class="actor-h"><span class="tag m">実行</span><b>実行を始める。〜 実行を終わる。</b></div>' +
      card("cm", "最初に一度だけ実行される部分", "", chart("実行を始める", "実行を終わる", main), "実行.svg") + "</div>";
    links.push('<a href="#cmain" class="chip m">実行</a>');
    out.innerHTML = html; toc.innerHTML = links.join("");
    show(true, "✓ アクター " + defs.length + " 個・受信節 " + count + " 個の流れ図を描きました（受信節ごとに 1 枚、それと「実行」の 1 枚）。");
  }
  out.addEventListener("click", function (e) {
    var b = e.target.closest(".dl"); if (!b) return;
    var svg = b.closest(".chart").querySelector("svg").outerHTML;
    var a = document.createElement("a");
    a.href = URL.createObjectURL(new Blob(['<?xml version="1.0" encoding="UTF-8"?>\n' + svg], { type: "image/svg+xml" }));
    a.download = b.getAttribute("data-f"); document.body.appendChild(a); a.click(); a.remove();
    setTimeout(function () { URL.revokeObjectURL(a.href); }, 1000);
  });
  KOTONOHA_SAMPLES.forEach(function (s, i) {
    var o = document.createElement("option"); o.value = i; o.textContent = s.title; sel.appendChild(o);
  });
  var timer = null;
  src.addEventListener("input", function () { clearTimeout(timer); timer = setTimeout(render, 400); });
  sel.addEventListener("change", function () { src.value = KOTONOHA_SAMPLES[+sel.value].text; render(); });
  $("drawBtn").addEventListener("click", render);
  var first = 0;
  KOTONOHA_SAMPLES.forEach(function (s, i) { if (/ユークリッド/.test(s.title)) first = i; });
  var q = /[?&]s=(\d+)/.exec(location.search); if (q && KOTONOHA_SAMPLES[+q[1]]) first = +q[1];
  sel.value = first; src.value = KOTONOHA_SAMPLES[first].text; render();

  if (typeof window !== "undefined") window.KotoFlow = { chart: chart, build: build };
})();
