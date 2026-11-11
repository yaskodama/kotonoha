# ことのは 文章形式（インデントなし）の文法と bison 検査

- `kotonoha.y` … 文法本体（一文方式・厳格版）。解析しながら構造化形式（インデントあり）を書き出す。
- `文法_BNF.txt` … 上の文法を日本語の終端記号で書き直した BNF（`python3 make_bnf.py` で再生成）
- `lex.py` … 字句解析器（予約語と宣言済みの名前を最長一致）
- `哲学者_文章形式.txt` … 5人の哲学者問題（フォークをアクターとする版）
- `許容版/kotonoha_nested.y` … 条件の本体に条件を直接書ける版。衝突1件（else の付き先）を `%expect 1` で明記
- `tests/` … else の付き先、「その後、」の位置

## 作り方と実行
    BISON=/opt/homebrew/opt/bison/bin/bison     # 3.8.2（macOS 付属の 2.3 は -Wcounterexamples 不可）
    $BISON -d -Wall -Wcounterexamples -r all --report-file=kotonoha.report -o kotonoha.tab.c kotonoha.y
    cc -w -o kotonoha kotonoha.tab.c
    python3 lex.py 哲学者_文章形式.txt | ./kotonoha      # 構造化形式が出る

## 検査結果（2026-11-11）
- 厳格版: 衝突 0、状態 185、規則 90（11/11 午後に計算・要素数・範囲の式を追加。追加前は 171／85）。哲学者のプログラムを解析し構造化形式へ変換できた。
- 許容版: shift/reduce 衝突 1（SOUDENAKEREBA）。シフト優先で「一番近いならば」に付く。

## 逆方向（構造化形式 → 文章形式）
    python3 to_bunsho.py 哲学者_構造化形式.txt > 哲学者_文章形式_逆変換.txt
    ./roundtrip.sh 哲学者_文章形式.txt        # 往復検査（-p で許容版）
- 構造化形式は「以上。」で閉じるので行単位で読む（字下げは見ていない）。
- 出るのは標準形: 「その」は消え、単純な文は3つまで「、」でつなぐ。代入は「の」を含めば「設定する」、それ以外は「変更する」。
- 往復検査の合格条件: 構造 S1 = S2（一字一句）、かつ 文章' が再変換で変わらない。4本すべて合格（2026-11-11）。

## 紹介ページ https://kodamay.org/kotonoha/ （2026-11-11 公開、認証なし）
- 原稿 `web/site/index.src.html`・`web/site/app.js`。`web/publish_local.sh` で ~/kodamay_org_site/kodamay.org/kotonoha/ に組み立てる
  （BNF と見本は ~/kotonoha の原本から差し込む）。上げるのは lftp mirror -R --no-perms。
- ブラウザの解析器は kotonoha.y → `web/y2jison.py` → jison（**-p lr**。jison の LALR は偽の衝突を出す）→ runtime.js に埋め込み。
- 検査: `node web/test_parity.mjs ../哲学者_文章形式.txt ../tests/*.txt`（C/Python と一致）、`TMPD=… node web/fuzz.mjs`（変異300本）。

## ブラウザ上の実行系（2026-11-11 追加）
- `web/runtime.js` の makeRun。構造化形式を parseProgram で構文木にし、アクター（受信箱つき）として解釈する。
  動く順は random（種つき mulberry32）か fifo。止まったとき状態の配列に残るアクターを「待っている」と報告。
- 検査 `node web/run_test.mjs 1000`: 安全版 1000/1000 満腹、左から取る版 721/1000 デッドロック。

## 例題（2026-11-11 追加） `例題/`
- ユークリッドの互除法・ハノイの塔（返事を待つ再帰、4枚15手）・バブルソート・クイックソート（左右を子アクターが並列に）。
- そのために足した文法: 計算「（AにBを加えた数）（AからBを引いた数）（AをBで割った余り）」は項として書ける（記号 arith）、
  「Xの要素数」、繰り返しの範囲は式（構造化形式では数以外を（…）で囲む＝bnd）、「列の（i）番目を…に設定する」は要素への代入。
- ついでに直した既存の不具合: 「AとBをXに追加する」の構造化形式で区切り文字が漏れていた（join 漏れ）。
- 表示の並べ方を変更: 空白は値と値の間だけ（「…」の前後は詰める）。哲学者の表示は「哲学者4が考えています」に書き換えた。
- 待ちの報告は「アクターだけが並ぶ配列」に限った（依頼の組に自分自身を入れても誤報しない）。
- 検査: 往復 10/10、C/Python と JS 一致 10/10、変異 300 一致、例題 4 本×種 1〜300 すべて正解。

## Xinu の見本の書き換え（2026-11-11）`例題/Xinuの挨拶.txt`
- PC Xinu（~/projects/xinu-mac/xinu-vbox/system/main.c）の greeter 2つを、挨拶係アクター＋見届け係で書き換え。sleepms の代わりに自分へ「挨拶」を送り直し、終わりは「終わった」を2つ数えて告げる。
- 届いた順（fifo）で Xinu の出力と1行ずつ一致。乱数順では Alice と Bob の混ざり方が変わる。
- そのために直した不具合: 字句解析（lex.py と runtime.js の strip）が「…」の中の空白まで捨てていた。文字列の中だけ空白を残す。
- 検査: 往復 11/11（入れ子の条件は -p）、C/Python と JS 一致 11/11、変異 300 一致、哲学者 安全版 300/300。

## PC Xinu の上で動かす（2026-11-11）`xinu/`
- `k2xinu.mjs` ことのは→C 変換器（構文木と式の読み方は web/kotonoha.js と共通）。`krt.c/krt.h` は Xinu 用の実行時ライブラリ。
- アクター1つ＝Xinu のプロセス1つ（受信箱＝連結リスト＋セマフォ）。受信節は大域の錠の中で一つずつ実行し、終わるたびに resched で同じ優先度の相手に譲る。
  処理待ちのメッセージが0になったら main に合図し、そのあと xsh を起動する。動く順は Xinu のスケジューラが決める。
- `./run_on_xinu.sh 例題.txt`（画面なしで出力だけ）／`-i`（対話）。組み込み先は ~/projects/xinu-mac/xinu-vbox/system/（main.c は kotonoha_main() を呼ぶよう書き換え、git は未コミット）。
- 検査: 挨拶・ハノイ・互除法・バブル・クイックの5本でブラウザ版（fifo）と出力の行集合が一致、哲学者（安全版）も 食事15回・満腹5人。

## Xinu の上の開発環境（2026-11-11）`xinu/gui/` ＋ `xinu/install.sh`
- PC Xinu に**マルチウィンドウシステム**（gui/wm.c：重なり・題名で移動・右下で大きさ・メニュー帯）と、
  **Smalltalk 風のブラウザ**（プログラム｜アクター定義｜受信節＋ソース）、実行・アクター・インスペクタ・デバッガ・トランスクリプトの窓（gui/kgui.c）を載せた。
- 画面は QEMU 標準 VGA の Bochs VBE（1024x768x32、gui/gfx.c）。裏画面は物理 8MB 番地。そのため system/i386.c でデータ/スタックのセグメント上限を 4GB に広げた。
  文字は jiskan16＋8x13（gui/jpfont.c、gui/tools/gen_jpfont.py で生成）。マウスは vmmouse の絶対座標（gui/input.c）、キーは i8042 を見回り。
- デバッガ: 生成コードは各文の前に kstep()。停止点（ブラウザで行番号の左をクリック）・1文（F7）・続ける（F5）・一時停止（F8）・中止・最初の文で止める。
  止まっている間は錠を持ったまま＝全体が止まる。局所変数・状態・受信箱が見える。誤りは行番号つきで報告。終了時に「待ち」の配列が残っていればデッドロックの疑いとして報告。
- 構文木に行番号（文 .line、受信節/定義 .line/.end、実行部 body.line/.end）を持たせた（web/runtime.js の _tree）。
- 組み込み: `xinu/install.sh`（例題5本＋哲学者2本。`EXTRA=ファイル` で追加）。起動: `~/projects/xinu-mac/run-xinu-gui.sh`。
- 画面なしの検査: `xinu/test/boot.sh SOCK SERIAL` で起動し `xinu/test/qmp.py SOCK click X Y key f7 shot out.png …`。
- **大きい画面（2026-11-11 追記）**: 表の画面 2880x1800（VGA は `-device VGA,vgamem_mb=32`）、論理 1440x900 を縦横2倍で写す（Retina の Mac で 1 点＝2x2 画素、窓は 1440x932 ポイント）。
  文字は ui（既定 2＝32 ドット）。寸法は wm.h の U(n)=n*ui。メニュー帯右端の［文字を小さく／大きく］で切り替え、窓の並びも変わる（kgui.c の layout）。トランスクリプトは折り返す。
  裏画面は物理 8MB〜13.2MB（16MB の手前に null プロセスのスタック）。
- **Xinu 自身のソースを読む・再起動（2026-11-11 追記）**: 文字の既定を ui=1（16 ドット）に戻した。
  ブラウザの上にタブ［ことのは］［Xinu ソース］。後者はディレクトリ｜ファイル｜関数＋行番号つきソース（関数を選ぶとその範囲を黄色に）。
  ソースは install.sh が gui/tools/gen_xsrc.py で system/kxsrc.c に埋め込む（15 ディレクトリ・316 ファイル・2.8 万行・558 関数。カーネルは text 1.38MB、ヒープ上限 6MB の内側）。
  ［Xinu を再起動（ブート）］は i8042 に 0xFE（CPU リセット）。QEMU を `-no-reboot` なしで起動しているので、-kernel を読み直して Xinu が最初から立ち上がる。

## ことのはで書き直した Xinu（2026-11-11）`xinu/kxinu/`
- `核.txt`: Xinu の核をことのはで。カーネル＝アクター1つ（proctab などは欄ごとの表「状態表の（pid）番目」）。受信節の名前は Xinu の関数名そのまま:
  nulluser・create・resume・ready・resched・ctxsw・戻る(intr.S)・clkhandler・wakeup・sleepms(insertd)・semcreate・wait・signal・send・receive・getpid・kill・exit・xdone。
  各節の前の `※【system/xxx.c】名前：説明` が元の C との対応（gen_xsrc.py がこれを読む）。
- 約束: プロセス1つ＝アクター1つ。「走れ」で1歩進み、必ず核へシステムコールを1つ送る。核が「走れ」を送り返す（ctxsw・戻り値つき）ので走るのは常に1つ。
  関数呼び出しは自分へのメッセージ（受信箱は届いた順）。1歩＝1刻み＝100ms、出口は必ず clkhandler。ready は入れるだけで resched は出口で。pid は1から（1＝ヌル）。
- 見本: `見本_挨拶.txt`（system/main.c の greeter。出力は本物と同じ）、`見本_生産と消費.txt`（Comer の prodcons をセマフォ2つで＋send/receive）。
  install.sh が `kxinu/build/Xinu_*.txt`（核＋見本）を作り、「Xinu（ことのは版）挨拶／生産と消費」として組み込む。
- 検査: `node web/kx_run.mjs xinu/kxinu/核.txt xinu/kxinu/見本_挨拶.txt [種]`。動く順をランダムにしても種1〜100で出力が一致（核が切り替えを完全に握っている）。
  bison 解析・往復検査も合格。Xinu 上でも同じ出力・同じ通数（挨拶182通、生産と消費191通）。
- 処理系の制約で書き換えた所: 「Xの1番目に…を加える」は構造化形式が `\S+ は \S+ 足す` なので要素・経路に使えない → 「…を（…に…を加えた数）に設定する」。
  名前に「の」を入れない（経路の区切りになる）。16ドットフォントに「—」「▶」が無い。
- Xinu の GUI: ブラウザの［Xinu ソース］タブは［ことのは版］（グループ｜C のファイル｜受信節。※注釈は緑）と［C の原文］の切り替え。
  ことのは版から［C の原文］を押すと同じファイル・関数へ跳ぶ。［この Xinu を実行］でことのはタブに移って走らせる。

## Xinu のファイルシステムと、Xinu の中のコンパイラ（2026-11-11）`xinu/fs/` `xinu/kxc/`
- **ディスク**: QEMU に `~/projects/xinu-mac/xinu-disk.img`（16MB、IDE の1次主）。run-xinu-gui.sh と test/boot*.sh が付ける（テストは `DISK=` で別の像）。
- **KFS**（fs/kfs.c）: ATA PIO（割り込みなし）。区画0＝見出し"KFS1"、1〜16＝目録（64B×128）、32〜＝中身（ファイルごとに連続）。
  名前は47バイトまで、/ を含めてよい。入りきらない書き直しは後ろへ移す（compact で詰める）。再起動しても残る（system_reset で確認）。
- **保存**: `kx_save_kernel`（kxc/kxfiles.c）が kxinu/核.txt・見本2本（kxsrc.c に埋め込んだもの）と、組み込みの例題の元の文章形式を 例題/名前.txt に書く。空のディスクは自動で初期化。
- **コンパイラ**: 文章形式 → kxlex.c（lex.py と同じ切り方。名前の宣言の正規表現5つを手で移植）→ kxc.y（kotonoha.y と同じ規則で構文木を作る。bison 3.8、api.prefix kx）
  → kxcomp.c（名前の解決は k2xinu.mjs と同じ規則、構文木をたどる実行器、kprogram を組み立てる）。実行時ライブラリとデバッガ（krt.c）はそのまま使う。
  見本の先頭の `※ 先に読む: kxinu/核.txt` のファイルを前につなぐ（誤りの行はファイルと行に直して報告）。一覧の同名は置き換え（置き場ごと返す）。
- **使い方**: 画面の「ファイル」窓（［カーネルを保存］［コンパイル］［コンパイルして実行］［消す］。誤りの行は赤）。シェルでは `koto ls|cat|save|cc|run|rm|format|df|compact`。
- **検査**: test/boot_serial.sh＋test/serial.py でシリアルから koto を打つ。9本を Xinu の中でコンパイル・実行し、JS の実行系と行の集合と通数が一致
  （核＋見本の2本は行の並びまで一致）。核.txt 単独は実行部が無いので構文エラーになる（正しい）。Xinu でコンパイルしたものでも停止点で止まる。
- k2xinu の版と違う点: 要素への「加える」が使える（構造化形式を経ないため）。構造化形式の画面は文章形式の行をそのまま出す。

## PC Xinu への組み込み（このリポジトリから）
- Xinu 本体は https://github.com/yaskodama/xinu-vbox 。そこへ `git apply xinu/xinu-vbox.patch`（main.c・i386.c・shell.c・shprototypes.h の変更）。
- そのあと `xinu/install.sh`（ことのはの変換・コンパイラ・GUI・ファイルシステムを system/ に写してビルド）。起動は `run-xinu-gui.sh` と同じ引数で（xinu/README の記述を参照）。
