(function () {
  "use strict";
  var $ = function (id) { return document.getElementById(id); };
  var bunsho = $("bunsho"), kozo = $("kozo"), status = $("status"), sel = $("sample"), con = $("console");

  function show(ok, msg) { status.className = "status " + (ok ? "ok" : "err"); status.textContent = msg; }

  function forward() {
    try {
      var t0 = performance.now();
      kozo.value = Kotonoha.toKozo(bunsho.value);
      show(true, "✓ 文章形式を解析して、構造化形式に変換しました（" + Math.max(1, Math.round(performance.now() - t0)) + " ms）。");
      return true;
    } catch (e) { show(false, "✗ " + (e.message || e)); return false; }
  }
  function backward() {
    try {
      bunsho.value = Kotonoha.toBunsho(kozo.value);
      var again = Kotonoha.toKozo(bunsho.value);
      var same = again.trim() === kozo.value.trim();
      show(true, "✓ 構造化形式を文章形式に変換しました。" + (same
        ? "その文章をもう一度解析すると、元の構造化形式と一字一句同じになります。"
        : "（その文章を解析し直した構造化形式は、字下げなどが元と少し異なります）"));
    } catch (e) { show(false, "✗ " + (e.message || e)); }
  }

  /* ───── 実行 ───── */
  var timer = null, running = null;
  function line(text, cls) {
    var d = document.createElement("div"); d.textContent = text; if (cls) d.className = cls; con.appendChild(d);
  }
  function stop(msg) {
    if (timer) { clearTimeout(timer); timer = null; }
    running = null; $("runBtn").disabled = false; $("stopBtn").disabled = true;
    if (msg) line(msg, "warn");
  }
  function run() {
    stop();
    con.textContent = "";
    if (!forward()) { line("文章形式に文法の誤りがあるので実行できません（上の赤い表示を見てください）。", "err"); return; }
    var seed = Math.max(1, parseInt($("seed").value, 10) || 1), order = $("order").value;
    var r;
    try { r = Kotonoha.makeRun(bunsho.value, { seed: seed, order: order, verbose: $("verbose").checked, limit: 200000 }); }
    catch (e) { line(e.message || String(e), "err"); return; }
    running = r; $("runBtn").disabled = true; $("stopBtn").disabled = false;
    var slow = $("slow").checked, t0 = performance.now();
    line("── 実行開始（動く順: " + (order === "fifo" ? "送られた順" : "ばらばら・種 " + seed) + "）", "trace");
    (function tick() {
      if (running !== r) return;
      var res = r.step(slow ? 1 : 2000);
      res.lines.forEach(function (l) { line(l.text, l.kind === "trace" ? "trace" : ""); });
      con.scrollTop = con.scrollHeight;
      if (!res.done) { timer = setTimeout(tick, slow ? 120 : 0); return; }
      if (res.error) line(res.error, "err");
      else if (res.stoppedByLimit) line("メッセージが " + res.processed + " 通に達したので止めました（終わらないプログラムかもしれません）。", "warn");
      else {
        line("── 終了: どのアクターの受信箱も空になりました（処理したメッセージ " + res.processed + " 通、アクター " + r.actors() + " 個、" + Math.max(1, Math.round(performance.now() - t0)) + " ms）", "sum");
        var w = r.waiting();
        if (w.length) {
          line("ただし、まだ待たされているアクターがいます。誰も動けないまま止まっている（デッドロック）かもしれません:", "warn");
          w.forEach(function (x) { line("  ・" + x, "warn"); });
        }
      }
      stop();
    })();
  }

  KOTONOHA_SAMPLES.forEach(function (s, i) {
    var o = document.createElement("option"); o.value = i; o.textContent = s.title; sel.appendChild(o);
  });
  function load(i) {
    stop(); con.textContent = "";
    bunsho.value = KOTONOHA_SAMPLES[i].text; kozo.value = "";
    if (KOTONOHA_SAMPLES[i].expectError) {
      show(true, "この見本はわざと文法違反を含みます。「構造化形式へ ▶」を押すと、どこで止まるかが表示されます。");
    } else forward();
    if (!KOTONOHA_SAMPLES[i].expectError) line("「▶ 実行」を押すと、このプログラムが動きます。", "trace");
  }
  sel.addEventListener("change", function () { load(+sel.value); });
  $("toKozo").addEventListener("click", forward);
  $("toBunsho").addEventListener("click", backward);
  $("runBtn").addEventListener("click", run);
  $("stopBtn").addEventListener("click", function () { stop("（停止しました）"); });
  $("seedBtn").addEventListener("click", function () { $("seed").value = (parseInt($("seed").value, 10) || 1) + 1; run(); });
  [bunsho, kozo].forEach(function (ta) {
    ta.addEventListener("keydown", function (e) {
      if ((e.metaKey || e.ctrlKey) && e.key === "Enter") { e.preventDefault(); (ta === bunsho ? forward : backward)(); }
    });
  });
  load(0);
})();
