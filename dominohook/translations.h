#pragma once

#include <array>

typedef enum {
    Push,
    Address,
    MovEAX,
    MovEDI,
    MovEBP,
    MovPtrESP,
    MovPtrEBP,
    MovPtr,
} StringPatchType;

typedef struct {
    StringPatchType type;
    size_t addr;
    const char* string;
    unsigned char offset = 0;
    size_t dst = 0;
} StringPatch;

StringPatch g_string_patches[] = {

    // キー設定をファイルに書き出せませんでした。
    {StringPatchType::Push, 0x401390 + 0x4F, "The key configuration could not be exported."},

    // このファイルはショートカットキー設定ファイルではありません。\n
    {StringPatchType::Push, 0x401570 + 0xEA, "This is not a valid shortcut key configuration file:\n\n"},

    // ショートカットキー設定ファイルの読み込みに失敗しました。\n
    {StringPatchType::Push, 0x401570 + 0x5D, "Failed to load shortcut key configuration file:\n\n"},

    // バックアップ保存 - %s
    {StringPatchType::Push, 0x402640 + 0x261, "Backup - %s"},

    // ディスプレイドライバ : %s
    {StringPatchType::Push, 0x4037B0 + 0x291, "Display Driver: %s\n"},

    // モニタ : %s
    {StringPatchType::Push, 0x4037B0 + 0x240, "Monitor: %s\n"},

    // メモリ : %s
    {StringPatchType::Push, 0x4037B0 + 0x1EF, "Memory: %s\n"},

    //   （症状や、再現する手順をここへ書き込んでください）
    {StringPatchType::Push, 0x4037B0 + 0x128, "(From here, indicate the problem or misbehavior of the program and or how it is reproduced.)\n"},

    // 不具合報告
    {StringPatchType::Push, 0x4037B0 + 0x6E, "Bug Report\n"},

    // 不明
    {StringPatchType::Push, 0x40443D, "unknown"},
    {StringPatchType::Push, 0x404510 + 0x1BE, "unknown"},

    // %d/%d MB （仮想 %d/%d MB）
    {StringPatchType::Push, 0x404720 + 0x160, "%d/%d MB (Virtual Memory: %d/%dMB)"},

    // %d / %d MB （仮想 %d / %d MB）
    {StringPatchType::Push, 0x404720 + 0xEC, "%d / %d MB (Virtual Memory: %d / %d MB)"},

    // イベントグラフ%d内容
    {StringPatchType::Push, 0x405010 + 0x40, "Graph Panel %d Macro Box"},

    // 置換後のマクロID
    {StringPatchType::Push, 0x405C20 + 0x6D, "Replacement ID"},

    // 検索マクロID
    {StringPatchType::Push, 0x405C20 + 0x5A, "Target ID"},

    // 置換内容を設定してください。
    {StringPatchType::Push, 0x406AB0 + 0x2E, "Please set up at least one entry."},

    // 追加
    {StringPatchType::MovEAX, 0x406E10 + 0x4C, "New"},

    // 編集
    {StringPatchType::MovEAX, 0x406E10 + 0x45, "Modification"},

    // (検索マクロID),(置換後のマクロID)\n(検索マクロID),(置換後のマクロID)\n・・・\n\nというような書式で文字列データを入力してください。\n区切りはカンマまたはタブに対応しています。\nコピーペーストも可能です。\n[OK]ボタンをクリックすると、内容を解析して置換リストへ追加します。
    {StringPatchType::Push, 0x4070A0 + 0x8, ""}, // Translation is migrated to resource data

    // 小節 %d にスケールが設定されていません。
    {StringPatchType::Push, 0x408C90 + 0x18A, "The key scale for measure %d is not yet configured."},

    // キースケール外のノートが存在します。\n続行しますか？
    {StringPatchType::Push, 0x408C90 + 0x143, "The notes are off from its key scale. Continue?"},

    // ファイルのオープンに失敗しました。
    {StringPatchType::Push, 0x409300 + 0x72, "Unable to open the file."},
    {StringPatchType::Push, 0x409750 + 0x70, "Unable to open the file."},

    // データ保存中にエラーが発生しました。\n保存を中止します。
    {StringPatchType::Push, 0x409410 + 0x31B, "An error has occurred while saving data.\nThe operation was aborted."},

    // データ圧縮中にエラーが発生しました。\n保存を中止します。
    {StringPatchType::Push, 0x409410 + 0x180, "An error has occurred during data compression.\nThe operation was aborted."},

    // 圧縮ライブラリの初期化に失敗しました。
    {StringPatchType::Push, 0x409410 + 0xEF, "Failed to initialize compression library."},
    {StringPatchType::Push, 0x409860 + 0x148, "Failed to initialize compression library."},

    // データ読み込み中にエラーが発生しました。
    {StringPatchType::Push, 0x409860 + 0x332, "An error has occurred while loading the data.\nThe operation was aborted."},

    // 圧縮データ展開中にエラーが発生しました。
    {StringPatchType::Push, 0x409A25, "An error has occurred while decompressing the data."},

    // ファイルの種類が異なります。
    {StringPatchType::Push, 0x409860 + 0xD2, "Invalid file type."},

    // イベントの追加
    {StringPatchType::Push, 0x40A7B0 + 0x6, "Event Add"},

    // 一括変更
    {StringPatchType::Push, 0x40AB40 + 0x33, "Modify..."},
    {StringPatchType::Push, 0x40B660 + 0x33, "Modify..."},

    // CC Valueの挿入
    {StringPatchType::Push, 0x40B920 + 0x6, "Insert CC Value"},

    // コントロールチェンジの置換
    {StringPatchType::Push, 0x40BE90 + 0x6, "Replace CC#"},

    // コントロールチェンジの置換（複数）
    {StringPatchType::Push, 0x40C300 + 0x6, "Multi Replace CC#"},

    // ハモリパートの生成
    {StringPatchType::Push, 0x40C570 + 0x6, "Harmonize"},

    // ベロシティコンプレッサ
    {StringPatchType::Push, 0x40CEB0 + 0x6, "Velocity Compressor"},

    // 重複ノートの一括補正
    {StringPatchType::Push, 0x40D000 + 0x6, "Fix Gate Overlaps"},

    // 重複ノートはありません。
    {StringPatchType::Push, 0x40D0B0 + 0x204, "The selection contains no overlapping note gates."},

    // イベントの削除
    {StringPatchType::Push, 0x40D380 + 0x6, "Event Delete"},
    {StringPatchType::Push, 0x40DE30 + 0x65, "Event Delete"},

    // 範囲の削除
    {StringPatchType::Push, 0x40D680 + 0x33, "Selection Deletion"},
    {StringPatchType::Push, 0x491980 + 0xCB, "Delete Selection"}, // Mouse button action
    {StringPatchType::Push, 0x4E3610 + 0x9D, "Delete Selection"}, // Mouse button action

    // イベントの削除(詰める)
    {StringPatchType::Push, 0x40DF30 + 0x6, "Event Ripple Deletion"},

    // 時間削除
    {StringPatchType::Push, 0x40E930 + 0x6, "Time Deletion"},

    // End of Trackの調節
    {StringPatchType::Push, 0x40ED60 + 0x6, "End of Track Marking"},

    // イベントリストMIDI入力
    {StringPatchType::Push, 0x40EF70 + 0x6, "Event List MIDI Input"},

    // エクスクルーシブ受信
    {StringPatchType::Push, 0x40F120 + 0x6, "Exclusive Reception"},

    // Fキーによる編集
    {StringPatchType::Push, 0x40F3A0 + 0x6, "Edit by F Key"},

    // 範囲ノートのGate補正
    {StringPatchType::Push, 0x40F7D0 + 0x6, "Fix Note Gate Range"},

    // ヒューマナイズ
    {StringPatchType::Push, 0x40F9E0 + 0x6, "Humanize"},

    // CCイベント挿入
    {StringPatchType::Push, 0x40FD20 + 0x6, "Insert CC Event"},

    // マークの挿入
    {StringPatchType::Push, 0x40FE00 + 0x6, "Add Marker"},
    {StringPatchType::Push, 0x4A9A3E, "Add Marker"},

    // イベントの挿入
    {StringPatchType::Push, 0x410800 + 0x3C, "Event Insertion"},
    {StringPatchType::Push, 0x410F00 + 0x6, "Event Insertion"},

    // MIDI INからノート挿入
    {StringPatchType::Push, 0x410510 + 0x6, "Insert Note from MIDI-IN"},

    // [MIDI-IN]の[入力情報の視聴]機能が動作していない場合は使用できません。
    {StringPatchType::Push, 0x4105C0 + 0x43, "This function cannot be utilized if Preview Input is disabled in the Preferences (MIDI-IN) window."},

    // 時間挿入
    {StringPatchType::Push, 0x411360 + 0x6, "Time Insertion"},

    // レガート
    {StringPatchType::Push, 0x4118D0 + 0x6, "Legato"},

    // メジャーリンクイベントの復元
    {StringPatchType::Push, 0x411A10 + 0x6, "Measure Link Utilization"},

    // EOT移動
    {StringPatchType::Push, 0x4120D0 + 0x6, "Move EOT"},

    // 範囲ノートの移動
    {StringPatchType::MovEAX, 0x4123C0 + 0x15, "Note Range Movement"},

    // 範囲ノートの複製を移動
    {StringPatchType::MovEAX, 0x4123C0 + 0xE, "Note Range Duplication"},

    // イベントの移動
    {StringPatchType::Push, 0x4126B0 + 0x6, "Anchor Adjustment"},
    {StringPatchType::MovEAX, 0x412900 + 0x15, "Anchor Adjustment"},

    // イベントの複製を移動
    {StringPatchType::MovEAX, 0x412900 + 0xE, "Event Duplication"},

    // 結合
    {StringPatchType::Push, 0x413380 + 0x6, "Merge"},

    // １オクターブ下げる
    {StringPatchType::MovEAX, 0x413820 + 0x15, "-1 Octave"},

    // １オクターブ上げる
    {StringPatchType::MovEAX, 0x413820 + 0xE, "+1 Octave"},

    // オニオンスキンノートの複製
    {StringPatchType::Push, 0x4138D0 + 0x6, "Mirror Onion Skin Note(s)"},

    // パーツ読み込み
    {StringPatchType::Push, 0x413C90 + 0x6, "Import parts from file"},
    {StringPatchType::MovEAX, 0x482B50 + 0xFB, "Import parts from file"},

    // クリップボードからのデータ読み込みに失敗しました。
    {StringPatchType::Push, 0x4144E7, "Failed to load data from clipboard."},

    // クリップボードのオープンに失敗しました。
    {StringPatchType::Push, 0x414470 + 0x63, "Failed to open clipboard."},
    {StringPatchType::Push, 0x4F63F0 + 0x2E, "Failed to open clipboard."},

    // 貼り付け
    {StringPatchType::Push, 0x4149A0 + 0xE5, "Paste"},
    {StringPatchType::Push, 0x491980 + 0xB4, "Paste"}, // Mouse button action
    {StringPatchType::Push, 0x4E3610 + 0x86, "Paste"}, // Mouse button action

    // 挿入貼り付け
    {StringPatchType::Push, 0x4149A0 + 0xA5, "Ripple Paste"},
    {StringPatchType::Push, 0x483010 + 0x5E, "Ripple Paste"}, // Import events paste mode

    // 置換貼り付け
    {StringPatchType::Push, 0x4149A0 + 0x69, "Ripple Replace"},
    {StringPatchType::Push, 0x483010 + 0x70, "Ripple Replace"}, // Import events paste mode

    // パターンスライス
    {StringPatchType::Push, 0x414BA0 + 0x6, "Pattern Slice"},

    // 歌詞の流し込み
    {StringPatchType::Push, 0x415030 + 0x6, "Lyric Bucket"},

    // イベントのプロパティ変更
    {StringPatchType::Push, 0x415610 + 0x6, "Event Modification"},
    {StringPatchType::Push, 0x415B00 + 0x5E, "Event Modification"},

    // クォンタイズ
    {StringPatchType::Push, 0x415C30 + 0x6, "Quantization"},

    // リアルタイム録音
    {StringPatchType::Push, 0x415F80 + 0x6, "Realtime Recording"},

    // 左右反転
    {StringPatchType::Push, 0x4163C0 + 0x6, "Flip"},

    // スライス
    {StringPatchType::MovEAX, 0x4165F0 + 0x15, "Slice"},

    // スライス（切り捨て）
    {StringPatchType::MovEAX, 0x4165F0 + 0xE, "Trim"},

    // Step変更
    {StringPatchType::Push, 0x416B10 + 0x3C, "Step Change"},

    // ステップ録音
    {StringPatchType::Push, 0x4171F0 + 0x6, "Step Recording"},

    // ステップ録音 タイ
    {StringPatchType::Push, 0x417710 + 0x6, "Step Recording Tie"},

    // ストローク
    {StringPatchType::Push, 0x417A40 + 0x6, "Stroke"},

    // タップテンポ＆フィット
    {StringPatchType::Push, 0x418890 + 0x6, "Tempo Tap && Fit"},

    // 指定範囲内にテンポイベントが存在します。\nあらかじめ削除した状態で実行してください。
    {StringPatchType::Push, 0x418950 + 0x67, "Tempo events already exist within the specified range."},

    // 拍ノートの数が足りません。
    {StringPatchType::Push, 0x4189D0 + 0x267, "Insufficient percussive notes."},

    // テンプレート挿入
    {StringPatchType::Push, 0x419160 + 0x6, "Template Insertion"},

    // テンポの挿入
    {StringPatchType::Push, 0x419390 + 0x6, "Insert Tempo"},

    // タイムストレッチ
    {StringPatchType::Push, 0x419710 + 0x6, "Time Stretch"},

    // トランスポーズ
    {StringPatchType::Push, 0x4198A0 + 0x6, "Transposition"},

    // 範囲のVel/Value補正
    {StringPatchType::Push, 0x419BC0 + 0x6, "Velocity Adjustment"},

    // ベロシティの変更
    {StringPatchType::Push, 0x41A050 + 0x6, "Velocity Adjustment"},

    // ファイルプロパティ
    {StringPatchType::Push, 0x41A570 + 0x6, "Project Properties"},

    // コマンド「%s」を実行中に例外が発生しました。\n\n例外が発生する手順を報告して頂けると助かります。
    {StringPatchType::Push, 0x41B430 + 0xCF, "An exception has occurred while running the command %s.\n\nPlease report to the developer how the exception occurred."},

    // 元に戻す(&U)
    {StringPatchType::Push, 0x41B6E0 + 0x1A, "Und&o"},

    // やり直す(&R)
    {StringPatchType::Push, 0x41B7A0 + 0x1A, "Red&o"},

    // コマンド「%s」をアンドゥ中に例外が発生しました。\n\n例外が発生する手順を報告して頂けると助かります。
    {StringPatchType::Push, 0x41B860 + 0xFF, "An exception has occurred while undoing the command [%s].\n\nPlease report to the developer how the exception occurred."},

    // コマンド「%s」をリドゥ中に例外が発生しました。\n\n例外が発生する手順を報告して頂けると助かります。
    {StringPatchType::Push, 0x41BA50 + 0xFF, "An exception has occurred while redoing the command [%s].\n\nPlease report to the developer how the exception occurred."},

    // トラックの削除
    {StringPatchType::Push, 0x41C590 + 0x6, "Remove Track(s)"},

    // トラックの挿入
    {StringPatchType::Push, 0x41D150 + 0x6, "Add Track(s)"},

    // デフォルトトラックの挿入
    {StringPatchType::Push, 0x41D5C0 + 0x6, "Add Track Set"},

    // トラックの移動
    {StringPatchType::Push, 0x41DA00 + 0x6, "Move Track(s)"},

    // トラックのプロパティ
    {StringPatchType::Push, 0x41EBF0 + 0x6, "Track Properties"},

    // 同期
    {StringPatchType::Push, 0x41FA20 + 0x279, "Synchronization"},

    // ポップアップメニュー
    {StringPatchType::Push, 0x41FA20 + 0x25A, "Pop-up Menus"},

    // デフォルトGate/Velocity
    {StringPatchType::Push, 0x41FA20 + 0x23B, "Default Gate/Velocity"},

    // マウス操作
    {StringPatchType::Push, 0x41FA20 + 0x21C, "Mouse Buttons"},
    {StringPatchType::Push, 0x426950 + 0x66, "Button",},

    // ファンクションキー
    {StringPatchType::Push, 0x41FA20 + 0x1FD, "Function Keys"},

    // ショートカットキー
    {StringPatchType::Push, 0x41FA20 + 0x1DE, "Shortcut Keys"},

    // バックアップ
    {StringPatchType::Push, 0x41FA20 + 0x1BF, "Backup"},

    // トラックリスト
    {StringPatchType::Push, 0x41FA20 + 0x1A0, "Tracklist"},
    {StringPatchType::Push, 0x4282B0 + 0x4F, "Tracklist"},

    // イベントグラフ (2)
    {StringPatchType::Push, 0x41FA20 + 0x181, "Graph Panel (pg. 2)"},

    // イベントグラフ (1)
    {StringPatchType::Push, 0x41FA20 + 0x162, "Graph Panel (pg. 1)"},

    // イベントリスト (3)
    {StringPatchType::Push, 0x41FA20 + 0x143, "Event List (pg. 3)"},

    // イベントリスト (2)
    {StringPatchType::Push, 0x41FA20 + 0x124, "Event List (pg. 2)"},

    // イベントリスト (1)
    {StringPatchType::Push, 0x41FA20 + 0x105, "Event List (pg. 1)"},

    // ピアノロール (2)
    {StringPatchType::Push, 0x41FA20 + 0xE6, "Piano Roll (pg. 2)"},

    // ピアノロール (1)
    {StringPatchType::Push, 0x41FA20 + 0xC7, "Piano Roll (pg. 1)"},

    // 全般 (3)
    {StringPatchType::Push, 0x41FA20 + 0x4B, "General (pg. 3)"},

    // 全般 (2)
    {StringPatchType::Push, 0x41FA20 + 0x2C, "General (pg. 2)"},

    // 全般 (1)
    {StringPatchType::Push, 0x41FA20 + 0xD, "General (pg. 1)"},

    // インポートに失敗しました。
    {StringPatchType::Push, 0x4209A0 + 0x11A, "Import failed."},

    // インポートに失敗しました。\n既存のiniフォルダの削除に失敗しました。
    {StringPatchType::Push, 0x4209A0 + 0x9E, "Import failed.\nFailed to delete existing ini file."},

    // この機能は、Windows2000以降でのみ動作します。
    {StringPatchType::Push, 0x420B10 + 0x37, "This function is only available in Windows2000 or later."},

    // 書き出しに失敗しました。
    {StringPatchType::Push, 0x420BA0 + 0xA1, "Export failed."},

    // そのキーは既に「%s」で使用されています。\n\n「%s」のキーをクリアし、「%s」へ割り当てますか？
    {StringPatchType::Push, 0x421400 + 0x175, "This key is already bound with [%s].\nWould you like to rebind [%s]'s keybind to [%s]'s?"},

    // キー割り当てを導入時の状態に戻します。\n\nよろしいですか？
    {StringPatchType::Push, 0x421A81, "Revert keybinds to its default configuration?"},

    // バックアップファイルの保存先を指定してください。
    {StringPatchType::Push, 0x422037, "Backup file save destination is not yet set. Set it up on the Preferences (Backup) window."},

    // 休符
    {StringPatchType::MovPtrESP, 0x423490 + 0x11C, "Rest Events", 0xAC - 0x1C},

    // コード
    {StringPatchType::MovPtrESP, 0x423490 + 0x106, "Chord Events", 0xAC - 0x24},

    // スケール
    {StringPatchType::MovPtrESP, 0x423490 + 0xF0, "Key Scale Events", 0xAC - 0x2C},

    // マーク
    {StringPatchType::MovPtrESP, 0x423490 + 0xE0, "Markers", 0xAC - 0x34},
    {StringPatchType::Push, 0x4AC860 + 0x9D, "Marker"},

    // 調号
    {StringPatchType::MovPtrESP, 0x423490 + 0xD0, "Key Signatures", 0xAC - 0x3C},
    {StringPatchType::Push, 0x4AC860 + 0xD0, "Key Signature"},


    // 拍子
    {StringPatchType::MovPtrESP, 0x423490 + 0xC0, "Rhythmic Signatures", 0xAC - 0x44},
    {StringPatchType::Push, 0x4AC860 + 0x6A, "Rhythmic Signature"},

    // メジャーリンク
    {StringPatchType::MovPtrESP, 0x423490 + 0xB0, "Measure Links"},

    // 変数代入式
    {StringPatchType::MovPtrESP, 0x423490 + 0xA0, "Variables", 0xAC - 0x54},
    {StringPatchType::Push, 0x4431D0 + 0x3E, "Variable"},

    // テンポ
    {StringPatchType::MovPtrESP, 0x423490 + 0x90, "Tempi", 0xAC - 0x5C},

    // キューポイント
    {StringPatchType::MovPtrESP, 0x423490 + 0x80, "Cue Points", 0xAC - 0x64},

    // 歌詞
    {StringPatchType::MovPtrESP, 0x423490 + 0x70, "Lyrics", 0xAC - 0x6C},

    // コメント
    {StringPatchType::MovPtrESP, 0x423490 + 0x60, "Comments", 0xAC - 0x74},

    // エクスクルーシブ
    {StringPatchType::MovPtrESP, 0x423490 + 0x50, "Exclusive Events", 0xAC - 0x7C},

    // コントロールチェンジ
    {StringPatchType::MovPtrESP, 0x423490 + 0x40, "Control Changes", 0xAC - 0x84},

    // プログラムチェンジ
    {StringPatchType::MovPtrESP, 0x423490 + 0x30, "Program Changes", 0xAC - 0x8C},

    // ノート
    {StringPatchType::MovPtrESP, 0x423490 + 0x20, "Note Events", 0xAC - 0x94},

    // %s - %s専用形式|*%s||
    {StringPatchType::Push, 0x4AA170 + 0x70, "Domino Song File (.dms)|*%s||"},

    // （未設定）
    {StringPatchType::Push, 0x4250D0 + 0x6E, "      "},

    // （未指定）
    {StringPatchType::MovEAX, 0x425680 + 0xA5, "(none)"},
    {StringPatchType::MovEAX, 0x425680 + 0x11A, "(none)"},
    {StringPatchType::Push, 0x425950 + 0x140, "(none)"},
    {StringPatchType::Push, 0x425B40 + 0x3E, "(none)"},
    {StringPatchType::Push, 0x425B40 + 0x74, "(none)"},
    {StringPatchType::Push, 0x425D00 + 0x281, "(none)"},
    {StringPatchType::Push, 0x4289E0 + 0x30, "(none)"},
    {StringPatchType::Push, 0x4289E0 + 0x14B, "(none)"},

    // デバイスに「%s」を指定した場合、\n音源欄には通常「%s」を指定してください。
    {StringPatchType::Push, 0x42646B, "The device [%s] is appropriately matched with the sound source [%s]."},

    // 音源（音源定義ファイル）
    {StringPatchType::Push, 0x4264F0 + 0x9C, "Sound Source"},

    // MIDI OUT デバイス
    {StringPatchType::Push, 0x426579, "MIDI-OUT Device"},

    // ポート
    {StringPatchType::Push, 0x426542, "Port"},

    // ▼
    {StringPatchType::Push, 0x426950 + 0x322, ">>"},

    // 動き
    {StringPatchType::Push, 0x426950 + 0x77, "Action"},

    // イベントリスト
    {StringPatchType::Push, 0x4282E2, "Event List"},

    // ピアノロール（イベントグラフ）
    {StringPatchType::Push, 0x4282C5, "Piano Roll/Graph Panel"},

    // リンク先のフォルダIDを指定してください : %s(%d)
    {StringPatchType::Push, 0x429301, "Specify the link destination's folder ID: %s (%d)"},

    // コントロールチェンジマクロIDを指定してください(%d〜%d) : %s(%d)
    {StringPatchType::Push, 0x4297F0 + 0x541, "Specify the Control Change Macro ID (%d~%d) : %s (%d)"},
    {StringPatchType::Push, 0x4372F0 + 0xA5F, "Specify the Control Change Macro ID (%d~%d) : %s (%d)"},
    {StringPatchType::Push, 0x4D52E0 + 0x4C8, "Specify the Control Change Macro ID (%d~%d) : %s (%d)"},

    // コントロールチェンジマクロのデータ「%s」が不明です : %s(%d)
    {StringPatchType::Push, 0x429CB1, "Unknown Control Change Macro data [%s]: %s (%d)"},

    // CCマクロのデータが構文エラーです。命令コマンドの引数に誤りがあります。正しくは「%s」です : %s(%d)
    {StringPatchType::Push, 0x42A597, "CC Macro Data syntax error. Instruction command argument is invalid. [%s] is suggested: %s (%d)"},

    // CCマクロのデータが構文エラーです。エクスクルーシブはF0Hから始めてF7Hで終わってください : %s(%d)
    {StringPatchType::Push, 0x42A551, "CC Macro Data syntax error. Exclusive events start with F0H and ends with F7H: %s (%d)"},

    // CCマクロのデータが構文エラーです。エクスクルーシブデータに処理できない値が含まれています : %s(%d)
    {StringPatchType::Push, 0x42A521, "CC Macro Data syntax error. The value contained in the exclusive event data cannot be processed: %s (%d)"},

    // CCマクロのデータが構文エラーです。チェックサム終了記号']'が必要です : %s(%d)
    {StringPatchType::Push, 0x42A4F1, "CC Macro Data syntax error. Missing checksum line close ']': %s (%d)"},

    // CCマクロのデータが構文エラーです。チェックサム終了記号']'が複数存在します : %s(%d)
    {StringPatchType::Push, 0x42A4C1, "CC Macro Data syntax error. Existing duplicate checksum line close ']': %s (%d)"},

    // CCマクロのデータが構文エラーです。チェックサム記号[....]の間にデータが存在しません : %s(%d)
    {StringPatchType::Push, 0x42A491, "CC Macro Data syntax error. Empty data within checksum line [....]: %s (%d)"},

    // CCマクロのデータが構文エラーです。チェックサム終了記号']'より前に開始記号'['が必要です : %s(%d)
    {StringPatchType::Push, 0x42A461, "CC Macro Data syntax error. Missing checksum line open '[' before line close ']': %s (%d)"},

    // CCマクロのデータが構文エラーです。エクスクルーシブデータにチェックサム開始記号'['が複数存在します : %s(%d)
    {StringPatchType::Push, 0x42A431, "CC Macro Data syntax error. Existing duplicate checksum line open '[' in exclusive data: %s (%d)"},

    // CCマクロのデータが構文エラーです。'@'の付くコマンドを最初に指示してください : %s(%d)
    {StringPatchType::Push, 0x42A401, "CC Macro Data syntax error. Assign the commands with '@' to the beginning: %s (%d)"},

    // リンク先のコントロールチェンジマクロIDを指定してください(%d〜%d) : %s(%d)
    {StringPatchType::Push, 0x42AD38, "Specify the link destination's Control Change Macro ID (%d~%d) : %s (%d)"},

    // 演奏時間パネル
    {StringPatchType::Push, 0x42BC20 + 0x6, "Time Panel"},

    // MS UI Gothic
    {StringPatchType::MovEAX, 0x42BD10 + 0x1ED, "MS Sans Serif"},
    {StringPatchType::Push, 0x4338E2, "MS Sans Serif"},
    {StringPatchType::Push, 0x433932, "MS Sans Serif"},
    {StringPatchType::Push, 0x433F50, "MS Sans Serif"},
    {StringPatchType::Push, 0x433F20 + 0x65, "MS Sans Serif"},
    {StringPatchType::Push, 0x4341A4, "MS Sans Serif"},
    {StringPatchType::Push, 0x434170 + 0x69, "MS Sans Serif"},
    {StringPatchType::Push, 0x450EA0 + 0x9D, "MS Sans Serif"},
    {StringPatchType::MovEAX, 0x4511A0 + 0x44, "MS Sans Serif"},
    {StringPatchType::MovEAX, 0x466950 + 0x1A1, "MS Sans Serif"},
    {StringPatchType::Push, 0x492590 + 0x9B, "MS Sans Serif"},
    {StringPatchType::Push, 0x4BECA0 + 0x46, "MS Sans Serif"},
    {StringPatchType::Push, 0x4DBF30 + 0x24C, "MS Sans Serif"},
    {StringPatchType::MovEAX, 0x4E5AD0 + 0x1D, "MS Sans Serif"},
    {StringPatchType::MovEAX, 0x4E5B30 + 0xB2, "MS Sans Serif"},
    {StringPatchType::MovEAX, 0x4E6CE0 + 0x39, "MS Sans Serif"},
    {StringPatchType::MovEAX, 0x4E91B0 + 0x86, "MS Sans Serif"},

    // ＭＳ ゴシック
    {StringPatchType::Push, 0x42BD88, "MS Sans Serif"},
    {StringPatchType::MovEDI, 0x43FB80 + 0xE4, "MS Sans Serif"},
    {StringPatchType::MovEDI, 0x43FB80 + 0x20B, "MS Sans Serif"},
    {StringPatchType::Push, 0x450BEC, "MS Sans Serif"},
    {StringPatchType::MovEDI, 0x4F4120 + 0x71, "MS Sans Serif"},
    {StringPatchType::MovEDI, 0x4F7750 + 0x1A, "MS Sans Serif"},

    // 直線・曲線
    {StringPatchType::Push, 0x42D240 + 0x6, "Graphing Tools"},

    // カスタマイズ
    {StringPatchType::Push, 0x42D2B0 + 0x122, "Customize..."},

    // フリーハンド
    {StringPatchType::Push, 0x42D6A0 + 0xC0, "Freehand"},

    // これ以上は追加できません。
    {StringPatchType::Push, 0x42E370 + 0x25, "Maximum entry count reached."},

    // ランダム
    {StringPatchType::Push, 0x42FCF0 + 0x127, "Random"},

    // Ｓ字曲線
    {StringPatchType::Push, 0x42FCF0 + 0xED, "S Curve"},

    // はやい曲線
    {StringPatchType::Push, 0x42FCF0 + 0xB3, "Ease out Curve"},

    // ゆるやかな曲線
    {StringPatchType::Push, 0x42FCF0 + 0x79, "Ease in Curve"},

    // 直線
    {StringPatchType::Push, 0x42FCF0 + 0x3C, "Line"},

    // 直線・曲線の間隔
    {StringPatchType::Push, 0x432A90 + 0x6, "Graphing Resolution"},

    // ファイルのオープンに失敗しました。\n
    {StringPatchType::Push, 0x432E70 + 0x99, "Failed to open file.\n\n"},

    // マークの小節指定は1以上にしてください : %s(%d)
    {StringPatchType::Push, 0x436920 + 0x18F, "Markers can only be on measures 1 and above: %s (%d)"},

    // 調号に 2424 は指定できません : %s(%d)
    {StringPatchType::Push, 0x4372F0 + 0xB56, "Cannot set %s as the Key Signature: %s (%d)"},

    // 拍子記号の分母に %d は指定できません : %s(%d)
    {StringPatchType::Push, 0x4372F0 + 0xAF9, "Cannot set %d as the Rhythmic Signature's denominator: %s (%d)"},

    // 拍子記号の分子に %d は指定できません : %s(%d)
    {StringPatchType::Push, 0x4372F0 + 0xADC, "Cannot set %d as the Rhythmic Signature's numerator: %s (%d)"},

    // 拍子記号を指定してください : %s(%d)
    {StringPatchType::Push, 0x4372F0 + 0xAB5, "Set up the Rhythmic Signature: %s (%d)"},

    // テンポを指定してください(%d〜%d) : %s(%d)
    {StringPatchType::Push, 0x4372F0 + 0xA8F, "Set up the Tempo (%d~%d): %s(%d)"},

    // コードイベントです。
    {StringPatchType::Push, 0x43BDC0 + 0x6, "Chord Event"},

    // コードの挿入
    {StringPatchType::Push, 0x43C7D0 + 0x2A, "Insert Chord Event"},

    // (%s: %d~%d)
    {StringPatchType::Push, 0x440010 + 0xBE, "(%s: %d~%d)"},

    // (%d〜%d)
    {StringPatchType::Push, 0x440010 + 0xA1, "(%d~%d)"},

    // キューポイントイベントです。
    {StringPatchType::Push, 0x441300 + 0x6, "Cue Point Event"},

    // キューポイントイベントのプロパティ
    {StringPatchType::Push, 0x4413D0 + 0x3D, "Cue Point Event Properties"},

    // キューポイント(&C) :  
    {StringPatchType::Push, 0x4413D0 + 0x21, "&Cue Point:"},

    // トラックの終端です。
    {StringPatchType::Push, 0x441630 + 0x6, "End of Track"},

    // エクスクルーシブイベントです。
    {StringPatchType::Push, 0x4418F0 + 0x6, "Exclusive Event"},

    // 最後は f7h で終わってください。
    {StringPatchType::Push, 0x441EB0 + 0x24B, "End the line with F7H."},

    // チェックサム終了記号 ']' が必要です。
    {StringPatchType::Push, 0x441EB0 + 0x226, "Missing checksum close line ']'. "},

    // 文字列データがダブルクォーテーションで閉じられていません。
    {StringPatchType::Push, 0x44209F, "String data are not closed by double quotation marks."},

    // 文字列データの中で「\」を使う場合は「\\」と入力してください。
    {StringPatchType::Push, 0x441EB0 + 0x1E7, "Input [\\\\] in the string data instead of using [\\]."},

    // 文字列データの書式が間違っています。
    {StringPatchType::Push, 0x442080, "Invalid string data format."},

    // コメントが閉じられていません。
    {StringPatchType::Push, 0x441EB0 + 0x1C8, "Comment line is not closed."},

    // コメントの書式が間違っています。
    {StringPatchType::Push, 0x441EB0 + 0x1BC, "Invalid comment format."},

    // 半角文字列以外の文字が含まれています。
    {StringPatchType::Push, 0x442032, "Only half-width characters are supported."},
    {StringPatchType::Push, 0x441EB0 + 0x1DB, "Only half-width characters are supported."},

    // 足し算/引き算のみ対応しています。
    {StringPatchType::Push, 0x4422C0 + 0x266, "Only addition/subtraction is supported"},

    // 演算結果が 0〜255（0H〜FFH） の範囲内に収まっていません。
    {StringPatchType::Push, 0x4422C0 + 0x25A, "Calculation result is not within the range of 0~255 (0H~FFH)."},

    // 足し算/引き算は連続して使えません。
    {StringPatchType::Push, 0x4422C0 + 0x1CE, "Operators cannot be used consecutively."},

    // 値は 0〜255（0H〜FFH） の範囲で指定してください。
    {StringPatchType::Push, 0x4422C0 + 0x161, "Specify a value within the range of 0~255 (0H~FFH)."},

    // チェックサム終了記号 ']' が複数存在します。
    {StringPatchType::Push, 0x4422C0 + 0xE1, "Existing duplicate checksum line close ']'."},

    // チェックサム記号 [...] の間にデータが存在しません。
    {StringPatchType::Push, 0x4422C0 + 0xC6, "Empty data within checksum line [...]."},

    // チェックサム終了記号 ']' より前に開始記号'['が必要です。
    {StringPatchType::Push, 0x4422C0 + 0xA6, "Missing line open '[' before checksum line close ']'."},

    // チェックサム開始記号 '[' が複数存在します。
    {StringPatchType::Push, 0x4422C0 + 0x65, "Existing duplicate checksum line open '['."},

    // 変数代入イベントです。
    {StringPatchType::Push, 0x443080 + 0x6, "Variable Event"},

    // 「=」が複数存在します。
    {StringPatchType::Push, 0x4438F0 + 0x1A9, "Existing duplicate [=]."},

    // 代入先の変数名が異常です。
    {StringPatchType::Push, 0x4438F0 + 0x17A, "The assigned variable name is invalid."},

    // 「代入先の変数名 = 数値または数式」となるように入力してください。
    {StringPatchType::Push, 0x4438F0 + 0xCE, "Input so that the assigned variable name represents a number or formula."},

    // これ以上登録する事は出来ません。
    {StringPatchType::Push, 0x444C47, "You cannot register any more."},

    // イベントグラフ - ペンツール
    {StringPatchType::Push, 0x445E30 + 0x6, "Graph Panel - Pen Tool"},

    // 描画 (%s, %d) → (%s, %d)
    {StringPatchType::Push, 0x4463C0 + 0x17B, "Graph (%s, %d) >> (%s, %d)"},

    // 描画 (%s, %.2f) → (%s, %.2f)
    {StringPatchType::Push, 0x4463C0 + 0x130, "Graph (%s, %.2f) >> (%s, %.2f)"},

    // 移動 (%s, %d) → (%s, %d)
    {StringPatchType::Push, 0x447360 + 0x19A, "Moved (%s, %d) >> (%s, %d)"},
    {StringPatchType::Push, 0x447360 + 0x1CC, "Moved (%s, %d) >> (%s, %d)"},

    // 移動 (%s, %.2f) → (%s, %.2f)
    {StringPatchType::Push, 0x447360 + 0x16A, "Moved (%s, %.2f) >> (%s, %.2f)"},

    // アンカー上で右ダブルクリック
    {StringPatchType::Push, 0x4478E0 + 0x9B, "Anchor Double Right-click"},

    // アンカー上で右クリック
    {StringPatchType::Push, 0x4478E0 + 0x84, "Anchor Right-click"},

    // アンカー上で中ダブルクリック
    {StringPatchType::Push, 0x4478E0 + 0x6D, "Anchor Double Middle-click"},

    // アンカー上で中クリック
    {StringPatchType::Push, 0x4478E0 + 0x56, "Anchor Middle-click"},

    // アンカー上で左ダブルクリック
    {StringPatchType::Push, 0x4478E0 + 0x3F, "Anchor Double Left-click"},

    // アンカー上で左クリック
    {StringPatchType::Push, 0x4478E0 + 0x28, "Anchor Left-click"},

    // ハンドスクロール
    {StringPatchType::Push, 0x4479C0 + 0xCB, "Hand scroll"},
    {StringPatchType::Push, 0x48F4A0 + 0x127, "Hand scroll"},
    {StringPatchType::Push, 0x491980 + 0x127, "Hand scroll"},
    {StringPatchType::Push, 0x4E3610 + 0xF9, "Hand scroll"},

    // プロパティの表示
    {StringPatchType::Push, 0x4479C0 + 0xB4, "Edit Event Properties"},

    // アンカー削除
    {StringPatchType::Push, 0x4479C0 + 0x9D, "Delete anchor"},

    // アンカー移動
    {StringPatchType::Push, 0x4479C0 + 0x86, "Move anchor"},

    // ポップアップメニューの表示
    {StringPatchType::Push, 0x4479C0 + 0x6F, "View pop-up menu"},
    {StringPatchType::Push, 0x48F4A0 + 0xB4, "View pop-up menu"},
    {StringPatchType::Push, 0x491980 + 0x9D, "View pop-up menu"},
    {StringPatchType::Push, 0x4E3610 + 0x6F, "View pop-up menu"},

    // ペン/選択ツールの切り替え
    {StringPatchType::Push, 0x4479C0 + 0x58, "Toggle Pen/Select Tool"},
    {StringPatchType::Push, 0x48F4A0 + 0x9D, "Toggle Pen/Select Tool"},
    {StringPatchType::Push, 0x491980 + 0x86, "Toggle Pen/Select Tool"},

    // 描画
    {StringPatchType::Push, 0x4479C0 + 0x41, "Graph"},

    // 無し
    {StringPatchType::Push, 0x4479C0 + 0x2A, "None"},
    {StringPatchType::Push, 0x48F4A0 + 0x2A, "None"},
    {StringPatchType::Push, 0x491980 + 0x2A, "None"},
    {StringPatchType::Push, 0x4B76E0 + 0x309, "None"},
    {StringPatchType::Push, 0x4E3610 + 0x2A, "None"},

    // Gate : %d → %d
    {StringPatchType::Push, 0x447F80 + 0x124, "Gate: %d >> %d"},
    {StringPatchType::Push, 0x48DD00+0x151, "Gate: %d >> %d"},

    // Vel/Value 補正 : %d
    {StringPatchType::Push, 0x448BA0 + 0xF5, "Vel/Value change: %d"},

    // 選択 (%s, %d) → (%s, %d)
    {StringPatchType::Push, 0x4492A0 + 0x70, "Selection from (%s, %d) >> (%s, %d)"},

    // クリックでこの値を挿入
    {StringPatchType::Push, 0x449930 + 0x13E, "Insert value by clicking"},

    // 調号イベントです。
    {StringPatchType::Push, 0x44E290 + 0x6, "Key Signature"},

    // 調号: %s
    {StringPatchType::Push, 0x44E580 + 0x58, "Key: %s"},

    // 調号の挿入
    {StringPatchType::Push, 0x44E840 + 0x12, "Insert Key Signature"},

    // あいうえお\n
    //{StringPatchType::Push, 0x4511A0 + 0x90, "aeiou"}, // I don't think this should be modified

    // Tick,Gate,Stepの桁: %d
    {StringPatchType::Push, 0x456340 + 0x6E, "Tick, Gate, Step: %d"},

    // Lyrics: 
    {StringPatchType::Push, 0x457D50 + 0xA, "Lyric: "},

    // 歌詞イベントです。
    {StringPatchType::Push, 0x457D80 + 0x6, "Lyric Event"},

    // 歌詞イベントのプロパティ
    {StringPatchType::Push, 0x457E50 + 0x3D, "Lyric Event Properties"},

    // 歌詞(&L) :  
    {StringPatchType::Push, 0x457E50 + 0x21, "&Lyric:"},

    // Mark: 
    {StringPatchType::Push, 0x458070 + 0xA, "Marker: "},

    // マークイベントです。
    {StringPatchType::Push, 0x4580A0 + 0x6, "Marker Event"},

    // マークイベントのプロパティ
    {StringPatchType::Push, 0x458170 + 0x3D, "Marker Event Properties"},

    // ラベル(&L) :  
    {StringPatchType::Push, 0x458170 + 0x21, "&Label:"},

    // MeasureLink
    {StringPatchType::Push, 0x4583B0 + 0x6, "Measure Link"},

    // Gate値として指定した小節と同じ演奏を行います。Value値でKey補正ができます。
    {StringPatchType::Push, 0x458680 + 0x6, "Measure Link event. Mirrors contents from a specific measure (Gate value). Transpose its contents using the event Value."},

    // ノートイベントです。
    {StringPatchType::Push, 0x459000 + 0x6, "Note Event"},

    // 音色を変更します。
    {StringPatchType::Push, 0x45B260 + 0x6, "Program Change"},

    // 前を検索
    {StringPatchType::Push, 0x45C400 + 0xBC, "Previous Entry"},

    // 次を検索
    {StringPatchType::Push, 0x45C400 + 0x9A, "Next Entry"},

    // 長さ %d を初期値として記憶しました。
    {StringPatchType::Push, 0x45DCCE, "The default length value is now %d."},

    // 休符イベントです。
    {StringPatchType::Push, 0x45DE20 + 0x6, "Rest Event"},

    // スケールイベントです。
    {StringPatchType::Push, 0x45E590 + 0x6, "Key Scale Event"},

    // スケールの挿入
    {StringPatchType::Push, 0x45F0A0 + 0x2A, "Insert Key Scale Event"},

    // テンポイベントです。
    {StringPatchType::Push, 0x45F910 + 0x6, "Tempo Event"},

    // コメントイベントです。
    {StringPatchType::Push, 0x460D80 + 0x6, "Comment Event"},

    // コメントイベントのプロパティ
    {StringPatchType::Push, 0x461040 + 0x3D, "Comment Event Properties"},

    // コメント(&C) :  
    {StringPatchType::Push, 0x461040 + 0x21, "&Comment:"},

    // 拍子イベントです。Event列で"4/4"などと入力できます。
    {StringPatchType::Push, 0x461630 + 0x6, "Rhythmic Signature"},

    // 拍子: %d/%d
    {StringPatchType::Push, 0x461970 + 0x3A, "Rhythm: %d/%d"},

    // 拍子の挿入
    {StringPatchType::Push, 0x461DF0 + 0x10, "Insert Rhythmic Signature"},

    // フォルダパスの取得に失敗しました。
    {StringPatchType::Push, 0x4621B0 + 0x87, "Failed to retrieve folder path."},
    {StringPatchType::Push, 0x482FD8, "Failed to retrieve folder path."},
    {StringPatchType::Push, 0x4835AC, "Failed to retrieve folder path."},

    // 登録されたパスはディレクトリではありません。\n\n
    {StringPatchType::Push, 0x462350 + 0x97, "This registered path is not a directory.\n\n"},

    // フォルダが存在しません。\n\n
    {StringPatchType::Push, 0x462350 + 0x53, "This folder does not exist.\n\n"},

    // 最近使ったファイル
    {StringPatchType::Push, 0x462900 + 0xC, "(empty)"},

    // 作業時間をリセットします。\n（リセット後に[キャンセル]ボタンを押しても元には戻りません。）\n\nよろしいですか？
    {StringPatchType::Push, 0x462EE7, "Time elapsed while running this project will be reset.\nThis cannot be undone!\nAre you sure about this?"},
    
    //  %d時間 %d分 %d秒
    {StringPatchType::Push, 0x462F10 + 0x75, "%dh : %dm : %ds"},

    // 曲名の初期値設定
    {StringPatchType::Push, 0x46320F, "Default Title Setup"},

    // 曲名の初期値を入力してください。
    {StringPatchType::Push, 0x4631F6, "Set up the initial title on new projects."},

    // 曲名の初期値(&D): 
    {StringPatchType::Push, 0x4631D2, "&Title:"},

    // 著作権の初期値設定
    {StringPatchType::Push, 0x46346F, "Default Label Setup"},

    // 著作権の初期値を入力してください。\n%y の部分は年に置き換えられます。
    {StringPatchType::Push, 0x463456, "Set up the copyright label on new projects.\n%y represents the current year."},

    // 著作権の初期値(&D): 
    {StringPatchType::Push, 0x463432, "&Label: "},

    // フォルダを選択してください。
    {StringPatchType::Push, 0x4667F0 + 0x17, "Please select a folder."},

    // 0除算しました。
    {StringPatchType::Push, 0x4675F2, "Divided by 0."},

    // 構文が間違っています。
    {StringPatchType::Push, 0x467548, "Syntax error."},
    {StringPatchType::Push, 0x46757E, "Syntax error."},
    {StringPatchType::Push, 0x4675B8, "Syntax error."},
    {StringPatchType::Push, 0x467629, "Syntax error."},
    {StringPatchType::Push, 0x467660, "Syntax error."},
    {StringPatchType::Push, 0x46767E, "Syntax error."},

    // "%s" は定義されていません。
    {StringPatchType::Push, 0x4676E0 + 0x59F, "\"%s\" is not defined."},

    // エラーが発生しました。
    {StringPatchType::Push, 0x467C57, "An error has occurred."},
    {StringPatchType::Push, 0x4F8860 + 0x13C, "An error has occurred."},

    // 全角文字には対応していません。
    {StringPatchType::Push, 0x467C41, "Full-width characters are not supported."},

    // '('が足りません。
    {StringPatchType::Push, 0x4680DE, "Missing line open '('."},

    // ファンクションキーバー
    {StringPatchType::Push, 0x469250 + 0x3, "Function Key Bar"},

    // デフォルトゲート
    {StringPatchType::Push, 0x469760 + 0x6, "Default Gate"},
    
    // iniファイルのセクション削除に失敗しました。
    {StringPatchType::MovPtrEBP, 0x46F410 + 0x3D, "Failed to delete .ini file section.", 0xD8},
    {StringPatchType::Push, 0x46F410 + 0x69, "Failed to delete .ini file section."},
    {StringPatchType::Push, 0x46F410 + 0xC7, "Failed to delete .ini file section."},
    {StringPatchType::Push, 0x46F410 + 0xED, "Failed to delete .ini file section."},
    
    // ユーザー定義ツールバー2
    {StringPatchType::MovPtrESP, 0x473310 + 0x170, "User Toolbar 2 ", 0xC8 - 0x24},

    // ユーザー定義ツールバー1
    {StringPatchType::MovPtrESP, 0x473310 + 0x140, "User Toolbar 1 ", 0xC8 - 0x38},

    // イベントリストMIDI入力ツールバー
    {StringPatchType::MovPtrESP, 0x473310 + 0x113, "Event List MIDI Input Toolbar ", 0xC8 - 0x4C},

    // イベントリストフィルターツールバー
    {StringPatchType::MovPtrESP, 0x473310 + 0xEE, "Event List Filter Toolbar ", 0xC8 - 0x60},

    // デフォルトGate/Veloツールバー
    {StringPatchType::MovPtrESP, 0x473310 + 0xC9, "Default Gate/Velocity Toolbar ", 0xC8 - 0x74},

    // エディットツールバー
    {StringPatchType::MovPtrESP, 0x473310 + 0xA4, "Editing Toolbar ", 0xC8 - 0x88},

    // メインツールバー
    {StringPatchType::MovPtrESP, 0x473310 + 0x7F, "Main Toolbar ", 0xC8 - 0x9C},

    // 音源（音源定義ファイル）が設定されました。\n[新規作成]を行うと、その音源専用の初期データが用意されます。\n\n今すぐ新規作成しますか？
    {StringPatchType::Push, 0x47442E, "A new sound source has been set. Its template is automatically set up on new projects. \nWould you like to create a new project?"},

    // 取扱説明書の表示に失敗しました。
    {StringPatchType::Push, 0x475C05, "User's Manual data is missing."},
    
    // 環境設定のエクスポート
    {StringPatchType::MovPtrESP, 0x47619E, "Export Preferences to file", 0xA4},

    // Domino専用環境設定ファイル(*.%s)|*.%s||
    {StringPatchType::Push, 0x476156, "Domino Configuration File (*.%s)|*.%s||"},
    {StringPatchType::Push, 0x4763C6, "Domino Configuration File (*.%s)|*.%s||"},

    // 環境設定のインポート
    {StringPatchType::MovPtrESP, 0x47640E, "Import Preferences from file", 0xA4},

    // マークバー
    {StringPatchType::Push, 0x476D60 + 0x8, "Marker Bar"},

    // MIDI入力デバイス「%s」が開けませんでした。
    {StringPatchType::Push, 0x478C20 + 0x58, "MIDI Input Device [%s] cannot be opened."},
    {StringPatchType::Push, 0x47B5A0 + 0xE1, "MIDI Input Device [%s] cannot be opened."},
    {StringPatchType::Push, 0x4BBEF0 + 0x91, "MIDI Input Device [%s] cannot be opened."},

    // MIDI出力デバイス「%s」が開けませんでした。
    {StringPatchType::Push, 0x47A6B0 + 0x59, "MIDI Output Device [%s] cannot be opened."},
    {StringPatchType::Push, 0x47BA10 + 0xCF, "MIDI Output Device [%s] cannot be opened."},

    // 定義ファイル読み込み中に例外が発生 : %s
    {StringPatchType::Push, 0x47C980 + 0x514, "An exception has occurred while loading the Definition File. (%s)"},

    // PitchBendRangeマクロIDを指定してください(%d〜%d) : %s(%d)
    {StringPatchType::Push, 0x47C980 + 0x38C, "Specify the Pitch Bend Range Macro ID (%d~%d): %s (%d)"},

    // PitchBendマクロIDを指定してください(%d〜%d) : %s(%d)
    {StringPatchType::Push, 0x47C980 + 0x327, "Specify the Pitch Bend Macro ID (%d~%d): %s (%d)"},

    // 定義ファイルにModuleDataタグが存在しません。 : %s
    {StringPatchType::Push, 0x47C980 + 0xBB, "Missing Module Data tag in Definition File. (%s)"},

    // PC番号は1〜128を指定してください : %s(%d)
    {StringPatchType::Push, 0x47CED0 + 0x514, "Specify the Program Change number (1~128): %s (%d)"},

    // Key番号は0〜127を指定してください : %s(%d)
    {StringPatchType::Push, 0x47CED0 + 0x4D2, "Specify the Key (0~127): %s (%d)"},
    
    // 値テーブルIDが重複しています(ID=%d) : %s(%d)
    {StringPatchType::Push, 0x47D480 + 0x4E5, "Existing duplicate value table ID (ID=%d): %s(%d)"},

    // 値テーブルIDを指定してください(0以上) : %s(%d)
    {StringPatchType::Push, 0x47D480 + 0x448, "Specify the value table ID (0 and above): %s(%d)"},

    // コントロールチェンジマクロID(%d)が重複しています。マクロ「%s」は破棄されます。
    {StringPatchType::Push, 0x47D480 + 0x23A, "Existing duplicate Control Change Macro ID (%d). Macro [%s] was discarded."},

    // 定義ファイルにポリフォニックキープレッシャーのマクロが存在しません : %s
    {StringPatchType::Push, 0x47E050 + 0x1F, "Existing Polyphonic Key Pressure Macro in Definition File: %s"},

    // 定義ファイルにチャネルプレッシャーのマクロが存在しません : %s
    {StringPatchType::Push, 0x47E090 + 0x28, "Existing Channel Pressure Macro in Definition File: %s"},

    // 定義ファイルにピッチベンドのマクロが存在しません : %s
    {StringPatchType::Push, 0x47E0D0 + 0x28, "Existing Pitch Bend Macro in Definition File: %s"},

    // ボリューム
    {StringPatchType::Push, 0x47E1D0 + 0xC2, "Volume"},

    // マスター
    {StringPatchType::Push, 0x47E280, "Master"},

    // ﾎﾞﾘｭｰﾑ
    {StringPatchType::Push, 0x47E1D0 + 0x9E, "Volume"},

    // ﾏｽﾀｰ
    {StringPatchType::Push, 0x47E25C, "Master"},

    // Moduleフォルダに音源定義ファイルを入れください。
    {StringPatchType::Push, 0x4803F5, "Please place Sound Source Definition files in the Module folder."},

    // 音源定義ファイルの先読みに失敗しました : %s
    {StringPatchType::Push, 0x480340 + 0x91, "The following Sound Source Definition file was not loaded: %s (The file could be either corrupted, moved, or name conflicted.)"},

    // 音源定義ファイルの音源名（%s）が重複しています : %s
    {StringPatchType::Push, 0x4804A0 + 0x1DF, "Existing duplicate Sound Source Definition file name: %s"},

    // 閉じる
    {StringPatchType::Push, 0x4818F0 + 0x135, "Close"},

    // パーツ書き出し
    {StringPatchType::MovEAX, 0x482B50 + 0x102, "Export parts to file"},

    // DMP - Dominoパーツ形式|*.dmp||
    {StringPatchType::Push, 0x482B50 + 0x2D, "Domino Parts File (*.dmp)|*.dmp||"},

    // 記憶しました。
    {StringPatchType::Push, 0x482FEC, "Successful!"},

    // 通常の貼り付け
    {StringPatchType::Push, 0x483010 + 0x4C, "Normal"},

    // ルートのフォルダを選択してください。
    {StringPatchType::Push, 0x4836A6, "Please select a root folder."},

    // パターンを選択してください。
    {StringPatchType::Push, 0x483F40 + 0x76, "Please select a pattern."},

    // パターンの登録
    {StringPatchType::Push, 0x484518, "Pattern Entry"},

    // パターン名を入力してください。
    {StringPatchType::Push, 0x4844FF, "Input the pattern's name."},
    {StringPatchType::Push, 0x48458F, "Input the pattern's name."},

    // パターン名(&P)
    {StringPatchType::Push, 0x4844E6, "&Name:"},

    // 未登録
    {StringPatchType::Push, 0x485450 + 0x49, "      "},
    
    // %d 分 %d 秒
    {StringPatchType::Push, 0x487CF0 + 0x59, "%dm : %ds"},

    // ループ範囲
    {StringPatchType::Push, 0x48ABC0 + 0x390, "Loop Range"},
    {StringPatchType::Push, 0x4E0DB0 + 0x3DF, "Loop Range"},

    // ピアノロール - 選択ツール
    {StringPatchType::Push, 0x48CA70 + 0x6, "Piano Roll - Select Tool"},

    // ピアノロール - ヘッダー
    {StringPatchType::Push, 0x48CC40 + 0x6, "Piano Roll - Header"},

    // ピアノロール - 鍵盤
    {StringPatchType::Push, 0x48CF00 + 0x6, "Piano Roll - Keyboard"},

    // ピアノロール - ペンツール
    {StringPatchType::Push, 0x48D210 + 0x6, "Piano Roll - Pen Tool"},

    // デフォルト値変更  Velocity : %d, Gate : %d
    {StringPatchType::Push, 0x48D440 + 0x488, "Default Values Modified (Velocity : %d, Gate : %d)"},

    // 移動 (%s, %s) → (%s, %s)
    {StringPatchType::Push, 0x48E040 + 0x1D5, "Moved (%s, %s) >> (%s, %s)"},

    // 配置 (%s, %s)
    {StringPatchType::Push, 0x48F230 + 0x120, "Insert (%s, %s)"},
    {StringPatchType::Push, 0x48FF90 + 0x227, "Insert (%s, %s)"},

    // ノート上で右ダブルクリック
    {StringPatchType::Push, 0x48F3C0 + 0x9B, "Note Double Right-click"},

    // ノート上で右クリック
    {StringPatchType::Push, 0x48F3C0 + 0x84, "Note Right-click"},

    // ノート上で中ダブルクリック
    {StringPatchType::Push, 0x48F3C0 + 0x6D, "Note Double Middle-click"},

    // ノート上で中クリック
    {StringPatchType::Push, 0x48F3C0 + 0x56, "Note Middle-click"},

    // ノート上で左ダブルクリック
    {StringPatchType::Push, 0x48F3C0 + 0x3F, "Note Double Left-click"},

    // ノート上で左クリック
    {StringPatchType::Push, 0x48F3C0 + 0x28, "Note Left-click"},

    // 上下ドラッグでVelocity変更
    {StringPatchType::Push, 0x48F4A0 + 0x183, "Adjust velocity (drag up/down)"},

    // オニオンスキンノートのトラックへ移動
    {StringPatchType::Push, 0x48F4A0 + 0x16C, "Switch to Onion Skin note's track"},

    // ドラッグでノートの複製を移動
    {StringPatchType::Push, 0x48F4A0 + 0x155, "Duplicate"},

    // スクラブ（部分再生）
    {StringPatchType::Push, 0x48F4A0 + 0x13E, "Scrub play"},
    {StringPatchType::Push, 0x491980 + 0x13E, "Scrub play"},

    // ノートのプロパティを表示
    {StringPatchType::Push, 0x48F4A0 + 0x110, "Edit Properties"},

    // ノートの削除
    {StringPatchType::Push, 0x48F4A0 + 0xF9, "Delete"},

    // ドラッグでノートの移動
    {StringPatchType::Push, 0x48F4A0 + 0xE2, "Drag"},

    // ノートからVelocityとGateをスポイト
    {StringPatchType::Push, 0x48F4A0 + 0xCB, "Use dropper"},

    // 音階プレビュー
    {StringPatchType::Push, 0x48F4A0 + 0x86, "Play key"},
    {StringPatchType::Push, 0x491980 + 0x58, "Play key"},

    // ノート配置（左右ドラッグでGate調節）
    {StringPatchType::Push, 0x48F4A0 + 0x6F, "Place note and adjust gate"},

    // ノート配置（ドラッグ対応）
    {StringPatchType::Push, 0x48F4A0 + 0x58, "Place note and drag"},

    // ノート配置
    {StringPatchType::Push, 0x48F4A0 + 0x41, "Place note"},

    // 配置 (%s, %s, %d)
    {StringPatchType::Push, 0x48FF90 + 0x1C0, "Place (%s, %s, %d)"},

    // Gate 補正 : %d
    {StringPatchType::Push, 0x490C00 + 0xBA, "Gate Adjustment: %d"},

    // 選択範囲上で右ダブルクリック
    {StringPatchType::Push, 0x4918A0 + 0x9B, "Selection Double Right-click"},
    {StringPatchType::Push, 0x4E3530 + 0x9B, "Selection Double Right-click"},

    // 選択範囲上で右クリック
    {StringPatchType::Push, 0x4918A0 + 0x84, "Selection Right-click"},
    {StringPatchType::Push, 0x4E3530 + 0x84, "Selection Right-click"},

    // 選択範囲上で中ダブルクリック
    {StringPatchType::Push, 0x4918A0 + 0x6D, "Selection Double Middle-click"},
    {StringPatchType::Push, 0x4E3530 + 0x6D, "Selection Double Middle-click"},

    // 選択範囲上で中クリック
    {StringPatchType::Push, 0x4918A0 + 0x56, "Selection Middle-click"},
    {StringPatchType::Push, 0x4E3530 + 0x56, "Selection Middle-click"},

    // 選択範囲上で左ダブルクリック
    {StringPatchType::Push, 0x4918A0 + 0x3F, "Selection Double Left-click"},
    {StringPatchType::Push, 0x4E3530 + 0x3F, "Selection Double Left-click"},

    // 選択範囲上で左クリック
    {StringPatchType::Push, 0x4918A0 + 0x28, "Selection Left-click"},
    {StringPatchType::Push, 0x4E3530 + 0x28, "Selection Left-click"},

    // 選択（追加）
    {StringPatchType::Push, 0x491980 + 0x155, "Additive select"},
    {StringPatchType::Push, 0x4E3610 + 0x127, "Additive select"},

    // 範囲の複製を移動
    {StringPatchType::Push, 0x491980 + 0x110, "Duplicate selection"},
    {StringPatchType::Push, 0x4E3610 + 0xE2, "Duplicate selection"},

    // 範囲の移動
    {StringPatchType::Push, 0x491980 + 0xF9, "Drag selection"},
    {StringPatchType::Push, 0x4E3610 + 0xCB, "Drag selection"},

    // 範囲のコピー
    {StringPatchType::Push, 0x491980 + 0xE2, "Copy selection"},
    {StringPatchType::Push, 0x4E3610 + 0xB4, "Copy selection"},

    // 選択範囲の解除
    {StringPatchType::Push, 0x491980 + 0x6F, "Deselect"},
    {StringPatchType::Push, 0x4E3610 + 0x58, "Deselect"},

    // 選択
    {StringPatchType::Push, 0x4E3610 + 0x41, "Select"},
    {StringPatchType::MovEBP, 0x4A4710 + 0x34, "Selection from"},
    {StringPatchType::Push, 0x491980 + 0x41, "Select"},

    // 選択 (%s, %s) → (%s, %s)
    {StringPatchType::Push, 0x491F40 + 0xB2, "Selection from (%s, %s) >> (%s, %s)"},

    // 区切り（セパレータ）です。
    {StringPatchType::Push, 0x49C520 + 0xA5, "Adds a separator line in between commands."},
    {StringPatchType::Push, 0x4D7DEF, "Adds a separator line in between commands."},

    // その位置へは移動出来ません。
    {StringPatchType::Push, 0x49CAB5, "Cannot move in that position"},

    // (メニューアイテムを挿入できます)
    {StringPatchType::Push, 0x49CDA0 + 0x32, "(Insert menu item/command)"},

    // 新しいサブメニュー(&A)
    {StringPatchType::Push, 0x49D0B3, "New sub-menu (&A)"},

    // 一つ以上のメニューコマンドを設定してください。
    {StringPatchType::Push, 0x49D240 + 0x41, "At least one or more menu command is required."},

    // このポップアップメニューの内容を導入時の状態に戻します。\n\nよろしいですか？
    {StringPatchType::Push, 0x49D2A7, "Revert this pop-up menu to its default configuration?"},

    // ポップアップメニューカスタマイズファイルの削除に失敗しました。\n
    {StringPatchType::Push, 0x49D9F0 + 0x51, "Failed to delete pop-up menu customization file.\n\n"},

    // 原因不明のエラーが発生しました。
    {StringPatchType::Push, 0x49DAB0 + 0x189, "An unknown error has occurred."},
    {StringPatchType::Push, 0x49DCB0 + 0x1F2, "An unknown error has occurred."},
    {StringPatchType::Push, 0x4CCF95, "An unknown error has occurred."},
    {StringPatchType::Push, 0x4CD095, "An unknown error has occurred."},

    // ポップアップメニューカスタマイズファイルのオープンに失敗しました。\n
    {StringPatchType::Push, 0x49DAB0 + 0x84, "Failed to open pop-up menu customization file.\n\n"},

    // ファイルは、ポップアップメニューカスタマイズファイルではありません。\n
    {StringPatchType::Push, 0x49DCB0 + 0xF3, "This file is not a pop-up menu customization file.\n\n"},

    // フォルダ構造が異常です。\nZIPはフォルダ構造を再現する形で解凍してください。
    {StringPatchType::Push, 0x49F380 + 0x111, "Invalid folder structure. \nExtract the original ZIP contents before running Domino."},

    // データの書き込みテストに失敗しました。\n%s は書き込み可能なフォルダへ配置してください。\n（Program Files以下などは書き込みが制限されています。）
    {StringPatchType::Push, 0x49FD40 + 0xD8, "Data write test failed.\nPlease move %s to a writable directory.\n(Program Files is not a possible location.)"},

    // 値または式を入力してください。
    {StringPatchType::Push, 0x4A4360 + 0x42, "Please input a value or formula."},

    // 選択 (%s) → (%s)
    {StringPatchType::Push, 0x4A4A50 + 0x62, "Selection from (%s) >> (%s)"},

    // 移動 (%d)
    {StringPatchType::Push, 0x4A4B20 + 0x28, "Move (%d)"},

    // 右ダブルクリック
    {StringPatchType::Push, 0x4A4BB0 + 0x98, "Double Right-click"},

    // 右クリック
    {StringPatchType::Push, 0x4A4BB0 + 0x81, "Right-click"},

    // 中ダブルクリック
    {StringPatchType::Push, 0x4A4BB0 + 0x6A, "Double Middle-click"},

    // 中クリック
    {StringPatchType::Push, 0x4A4BB0 + 0x53, "Middle-click"},

    // 左ダブルクリック
    {StringPatchType::Push, 0x4A4BB0 + 0x3C, "Double Left-click"},

    // 左クリック
    {StringPatchType::Push, 0x4A4BB0 + 0x25, "Left-click"},

    // 小節ソロ演奏開始
    {StringPatchType::Push, 0x4A4DE0 + 0x9A, "Play solo measure"},
    {StringPatchType::Address, 0x5ABE2C, "Play solo measure"},

    // ソロ演奏開始
    {StringPatchType::Push, 0x4A4DE0 + 0x83, "Play solo track"},

    // 停止
    {StringPatchType::Push, 0x4A4DE0 + 0x6C, "Stop playback"},

    // 演奏開始
    {StringPatchType::Push, 0x4A4DE0 + 0x55, "Start playback"},

    // やり直す
    {StringPatchType::Push, 0x4A4DE0 + 0x3E, "Redo"},
    {StringPatchType::Address, 0x5ABE20, "Redo"},

    // 元に戻す
    {StringPatchType::Push, 0x4A4DE0 + 0x27, "Undo"},
    {StringPatchType::Address, 0x5ABE14, "Undo"},
    
    // 新規作成用のファイルが開けませんでした。 : %s
    {StringPatchType::Push, 0x4A6B50 + 0xBF, "Custom new project file is invalid. (%s)"},

    // 新規作成用のファイルが指定されていません。[環境設定]を行ってください。
    {StringPatchType::Push, 0x4A6B50 + 0x3A, "Custom new project is not yet set in the Preferences (General (pg. 2)) window."},

    // 無題
    {StringPatchType::Push, 0x4A6F30 + 0x4A, "Untitled"},

    //  選択 
    {StringPatchType::MovEAX, 0x4A7190 + 0x3A, "Select"},

    // MIDI出力devに［音源］が設定されていません。［環境設定］から設定を行ってください。
    {StringPatchType::Push, 0x4A73F0 + 0x12F, "MIDI Device sound source is not yet set. Set it up in the Preferences (MIDI-OUT) window."},

    // MIDI出力デバイスが設定されていません。［環境設定］から設定を行ってください。
    {StringPatchType::Push, 0x4A73F0 + 0x120, "MIDI-OUT Device is not yet set. Set it up in the Preferences (MIDI-OUT) window."},

    // コピーに失敗しました。
    {StringPatchType::Push, 0x4A7570 + 0x48, "Copy failed."},
    {StringPatchType::Push, 0x4A8063, "Copy failed."},

    // 選択範囲をクリップボードへ保存しました。
    {StringPatchType::Push, 0x4A7570 + 0x35, "Copied highlighted events!"},

    // 元に戻しました : 
    {StringPatchType::Push, 0x4A7AE9, "Undo: "},

    // やり直しました : 
    {StringPatchType::Push, 0x4A7BF9, "Redo: "},

    // 指定したマークへ移動
    {StringPatchType::Push, 0x4A7E48, "(empty)"},

    // イベントをクリップボードへ保存しました。
    {StringPatchType::Push, 0x4A7F40 + 0x11C, "Copied event selection!"},

    // 指定したトラックの表示
    {StringPatchType::Push, 0x4A87C8, "Show specified track"},

    // ラベル(&L) : 
    {StringPatchType::Push, 0x4A9A26, "&Label: "},

    // 対応したすべての形式|*%s;*.mid|%s - %s専用形式|*%s|MID - Standard MIDI File|*.mid||
    {StringPatchType::Push, 0x4A9D50 + 0x9B, "Domino Song File or Standard MIDI File (*.dms; *.mid; *.midi)|*%s;*.mid;*.midi||"},

    // 保存しました。 : %s
    {StringPatchType::Push, 0x4AA050 + 0x9F, "Saved succesfully! (%s)"},

    // mid形式（SMF形式）で書き出すには、\n[ファイル]メニューの[SMF書き出し]を選んでください。\n\n保存を中止します。
    {StringPatchType::Push, 0x4AA170 + 0x19F, "To export as a MIDI file (SMF), select [Save MIDI] or [Export MIDI as...]in the [File] menu.\n\nThe operation was aborted."},

    // この形式には対応していません。\n
    {StringPatchType::Push, 0x4AA4A0 + 0x702, "Invalid file type.\n\n"},
    {StringPatchType::Push, 0x4AAE00 + 0x36F, "Invalid file type.\n\n"},

    // MIDIデータを解析してコントロールチェンジマクロを復元しますか？\n\n※ 解析には数分掛かることがあります。\n※ [環境設定]-[SMF]にて、このメッセージの有無を設定できます。
    {StringPatchType::Push, 0x4AA4A0 + 0x4B5, "Would you like to restore Control Change Macros?\n * Analysis might take several minutes.\n * This message can be disabled in the Preferences (SMF) window."},

    // MIDIファイルを読み込みます。\nよろしいですか？\n\n%s
    {StringPatchType::Push, 0x4AA4A0 + 0x8A, " Would you like to load the following?\n%s"},

    // クリップボードに保存しました : %s
    {StringPatchType::Push, 0x4AAE00 + 0x2BD, "Copied to clipboard! (%s)"},

    // %s への変更を保存しますか？
    {StringPatchType::Push, 0x4AB220 + 0x4E, "Would you like to save changes to %s?"},

    // このファイルにはMIDI-OUT設定情報が含まれています。\n\n設定を復元しますか？
    {StringPatchType::Push, 0x4AB330 + 0x6D, "This file contains MIDI-OUT configuration data.\n\nWould you like to restore the configuration?"},

    // 書き出しました : %s
    {StringPatchType::Push, 0x4AC860 + 0x4CF, "Exported sucessfully! (%s)"},

    // の情報が存在します。\n\n適切な位置で曲を終了させたい場合には、\nEnd of Trackより後ろの情報を削除してください。
    {StringPatchType::Push, 0x4AC9D8, "That data already exists.\n\nIf the song ends in an incorrect location, remove data after the End of Track event."},

    // 各トラックのEnd of Trackよりも後ろに
    {StringPatchType::Push, 0x4AC860 + 0xEB, "Before each track's End of Track event\n"},

    // コード : 
    {StringPatchType::Push, 0x4ADF44, "Chord: "},

    // パーツ保存しました。 : %s
    {StringPatchType::Push, 0x4AFA73, "Parts exported successfully! (%s)"},

    // %sの音量が%d％より小さいか、またはミュートになっています。ボリュームコントロールで音量を調節してください。
    {StringPatchType::Push, 0x4B0560 + 0x1C7, "Volume level of %s reached less than %d%. Adjust it using the volume control."},

    // %sの音量が%d％より小さいか、またはミュートになっています。\n音量を%d％に調節してもよろしいですか？
    {StringPatchType::Push, 0x4B0560 + 0x128, "Volume level of %s reached less than %d%.\nWould you like to adjust it up to %d%?  "},

    // プリセット名を入力してください。
    {StringPatchType::Push, 0x4B23A0 + 0x23, "Please input the preset name."},
    {StringPatchType::Push, 0x4B2440 + 0x24, "Please input the preset name."},

    // プリセットが見つかりませんでした。
    {StringPatchType::Push, 0x4B2440 + 0x53, "This preset cannot be found."},

    // 選択したデータをプリセットから削除
    {StringPatchType::Push, 0x4B28B0 + 0x57, "Delete selected data from presets"},

    // 現在のデータをプリセットへ保存
    {StringPatchType::Push, 0x4B28B0 + 0x36, "Save data to current preset"},

    // 小節
    {StringPatchType::Address, 0x5AB1E8, "Bar"},

    // ユーザー指定
    {StringPatchType::Address, 0x5AB1E0, "Custom..."},

    // 3連32分音符
    {StringPatchType::Address, 0x5AB1D8, "1/48"},

    // 32分音符
    {StringPatchType::Address, 0x5AB1D0, "1/32"},

    // 付点32分音符
    {StringPatchType::Address, 0x5AB1C8, "3/64"},

    // 3連16分音符
    {StringPatchType::Address, 0x5AB1C0, "1/24"},

    // 16分音符
    {StringPatchType::Address, 0x5AB1B8, "1/16"},

    // 付点16分音符
    {StringPatchType::Address, 0x5AB1B0, "3/32"},

    // 3連8分音符
    {StringPatchType::Address, 0x5AB1A8, "1/12"},

    // 8分音符
    {StringPatchType::Address, 0x5AB1A0, "1/8"},

    // 付点8分音符
    {StringPatchType::Address, 0x5AB198, "3/16"},

    // 3連4分音符
    {StringPatchType::Address, 0x5AB190, "1/6"},

    // 4分音符
    {StringPatchType::Address, 0x5AB188, "1/4"},

    // 付点4分音符
    {StringPatchType::Address, 0x5AB180, "3/8"},

    // 3連2分音符
    {StringPatchType::Address, 0x5AB178, "1/3"},

    // 2分音符
    {StringPatchType::Address, 0x5AB170, "1/2"},

    // 付点2分音符
    {StringPatchType::Address, 0x5AB168, "3/4"},

    // 全音符
    {StringPatchType::Address, 0x5AB160, "Whole"},

    // エクスクルーシブバッファ不足の可能性があります。環境設定で増やしてください。
    {StringPatchType::Push, 0x4B6810 + 0x5A, "Exclusive Reception Buffer size might not be enough. Set it up in the Preferences (MIDI-IN) window."},

    // キー
    {StringPatchType::Push, 0x4B6BB0 + 0xCC, "Key"},
    {StringPatchType::Push, 0x4BCB10 + 0xCC, "Key"},

    // 動作/機能
    {StringPatchType::Push, 0x4B6BB0 + 0xB9, "Functions"},
    {StringPatchType::Push, 0x4BCB10 + 0xB9, "Functions"},

    // レイアウトを反映させるには、リアルタイム録音画面を再表示させてください。
    {StringPatchType::Push, 0x4B6D20 + 0x4A, "Re-open the Realtime Recording window for the changes to take effect."},

    // オクターブ-
    {StringPatchType::Address, 0x5AB4FC, "Octave -"},
    {StringPatchType::Address, 0x5ABE44, "Octave -"},

    // オクターブ+
    {StringPatchType::Address, 0x5AB4F0, "Octave +"},
    {StringPatchType::Address, 0x5ABE38, "Octave +"},

    // 記録トラック
    {StringPatchType::Push, 0x4BA470 + 0xB1, "Recording Track"},

    // 入力チャンネル
    {StringPatchType::Push, 0x4BA470 + 0x9E, "Input Channel"},

    // MIDI IN デバイス
    {StringPatchType::Push, 0x4BA470 + 0x75, "MIDI-IN Device"},

    // MIDI-INデバイスが一つもありません。
    {StringPatchType::Push, 0x4BA8BC, "There are no registered MIDI-IN Devices."},

    // [詳細]ボタンをクリックし、複数チャンネル録音の詳細設定を行ってください。
    {StringPatchType::Push, 0x4BBEF0 + 0x2B, "Click the [Config...] button to set up Multiple Channel Recording."},

    // 前の小節へ
    {StringPatchType::Address, 0x5ABE08, "Previous Measure"},

    // 次の小節へ
    {StringPatchType::Address, 0x5ABDFC, "Next Measure"},

    // 確定後のタイ
    {StringPatchType::Address, 0x5ABDF0, "After Tie"},

    // 前
    {StringPatchType::Address, 0x5ABDE4, "Previous"},

    // 次/タイ
    {StringPatchType::Address, 0x5ABDD8, "Next/Tie"},

    // 3連符切り替え
    {StringPatchType::MovPtr, 0x4BD034, "Toggle Triplet", 0x0, 0x005AC168},

    // 付点切り替え
    {StringPatchType::MovPtr, 0x4BD01B, "Toggle Dotted", 0x0, 0x005AC15C},

    // 和音を検出しました: 範囲(%s)-(%s) （ここをダブルクリックすると該当範囲へ移動します）
    {StringPatchType::Push, 0x4C33B0 + 0x55B, "Detected chord: Range (%s) - (%s) (Double-click here to focus on the event.)"},

    // 対象の和音は見つかりませんでした。
    {StringPatchType::Push, 0x4C33B0 + 0x4B8, "Found no matches."},

    // 音階を2つ以上指定してください。
    {StringPatchType::Push, 0x4C3AE0 + 0x2B, "At least 2 or more key scales are required."},

    // メジャーリンクイベントの復元に失敗しました。
    {StringPatchType::Push, 0x4C3B20 + 0x50, "Failed to utilize the Measure Link event."},

    // 小節を指定してください。
    {StringPatchType::Push, 0x4C5D50 + 0x3AA, "Please specify the measure."},

    // 小節範囲が空です。
    {StringPatchType::Push, 0x4C5D50 + 0x89, "Empty measure."},

    // 一つも選ばれていません。
    {StringPatchType::Push, 0x4C8200 + 0x27, "None is selected."},

    // （全種類）
    {StringPatchType::Push, 0x4C9CA0 + 0x50, "(All)"},

    // 全トラック
    {StringPatchType::Push, 0x4C9FA0 + 0x5C, "All Tracks"},

    // １トラック内に複数のチャンネルが混合しています。\n読み込みを中止します。
    {StringPatchType::Push, 0x4CE2FB, "Multiple channels are mixed in 1 track.\n\nThe operation was aborted."},

    // 不明なチャンクを検出しました。
    {StringPatchType::Push, 0x4CE2ED, "An unknown channel has been detected."},
    {StringPatchType::Push, 0x4CE4B0 + 0x167, "An unknown channel has been detected."},

    // エスケープ形式のエクスクルーシブデータを読み飛ばします。
    {StringPatchType::Push, 0x4CDF68, "Skipped exclusive data in escape format."},
    {StringPatchType::Push, 0x4CF05B, "Skipped exclusive data in escape format."},

    // ピッチベンドチェンジイベントを破棄しました。
    {StringPatchType::Push, 0x4CD130 + 0x8D9, "Pitch Bends were discarded."},
    {StringPatchType::Push, 0x4CE4B0 + 0x7AE, "Pitch Bends were discarded."},

    // チャネルプレッシャーイベントを破棄しました。
    {StringPatchType::Push, 0x4CD130 + 0x81C, "Channel Pressures were discarded."},
    {StringPatchType::Push, 0x4CE4B0 + 0x6E4, "Channel Pressures were discarded."},

    // ポリフォニックキープレッシャーイベントを破棄しました。
    {StringPatchType::Push, 0x4CD130 + 0x6B7, "Polyphonic Key Pressures were discarded."},
    {StringPatchType::Push, 0x4CE4B0 + 0x56E, "Polyphonic Key Pressures were discarded."},

    // このファイルの時間単位(Division)には対応していません。
    {StringPatchType::Push, 0x4CD130 + 0x172, "The time unit (division) of this file is not supported:"},

    // 現在のバージョンではFormat0〜1以外は読み込めません。
    {StringPatchType::Push, 0x4CD130 + 0x123, "The current version only supports formats 0 and 1."},

    // Standard MIDI Fileではありません。
    {StringPatchType::Push, 0x4CD130 + 0xCE, "This is not a valid MIDI file:"},

    // ファイルを開けませんでした。
    {StringPatchType::Push, 0x4CD130 + 0x5A, "This file could not be opened: "},
    {StringPatchType::Push, 0x4CF528, "This file could not be opened: "},
    {StringPatchType::Push, 0x4D0480 + 0x9B, "This file could not be opened: "},

    // ノートとノートが重なっています : Track=%s, %s　（ここをダブルクリックすると該当イベントをフォーカスします）
    {StringPatchType::Push, 0x4CFDFE, "Overlapping notes: Track=%s, %s (Double-click here to focus on the event.)"},
    {StringPatchType::Push, 0x4D0480 + 0x795, "Overlapping notes: Track=%s, %s (Double-click here to focus on the event.)"},

    // ポートB以降のデータはSMF format0では書き出されません。
    {StringPatchType::Push, 0x4D04DE, "Data after Port B will not be exported as SMF format 0."},

    // MID - Standard MIDI File|*.mid||
    {StringPatchType::Push, 0x4D20B0 + 0x2C, "Standard MIDI File (.mid)|*.mid; *.midi||"},

    // format 1（通常はこちら）
    {StringPatchType::Push, 0x4D21D0 + 0xBE, "format 1"},

    // format 0
    {StringPatchType::Push, 0x4D21D0 + 0xA9, "format 0"},

    // ドラッグで上下に動かせます。\nダブルクリックで初期値に戻せます。
    {StringPatchType::Push, 0x4D25F0 + 0x9E, "Drag to move up/down.\nDouble-click to revert to default state."},

    // ドラッグで左右に動かせます。\nダブルクリックで初期値に戻せます。
    {StringPatchType::Push, 0x4D25F0 + 0x81, "Drag to move left/right.\nDouble-click to revert to default state."},

    // カスタムデータを入力してください。
    {StringPatchType::Push, 0x4D3510 + 0x3F, "Please input custom data."},

    // ↓↑ from [Event > Stroke]
    {StringPatchType::Push, 0x4D3570 + 0x74, "U"},
    {StringPatchType::Push, 0x4D3B8A, "U"},
    {StringPatchType::Push, 0x4D3570 + 0x8F, "D"},    
    {StringPatchType::Push, 0x4D3BDA, "D"},
    
    // 小節範囲を正しく設定してください。
    {StringPatchType::Push, 0x4D50C0 + 0x63, "Please specify the measure range correctly."},

    // コンダクタートラックは指定できません。
    {StringPatchType::Push, 0x4D50C0 + 0x35, "The Conductor Track cannot be specified."},

    // 新しい長さを設定してください。
    {StringPatchType::Push, 0x4D6BA0 + 0xE9, "Please specify a new length."},

    // 選ばれているコマンドの削除
    {StringPatchType::Push, 0x4D76A0 + 0x125, "Deletes the selected command"},

    // 選ばれているツールバーの名前変更
    {StringPatchType::Push, 0x4D76A0 + 0x108, "Changes the name of this toolbar"},

    // 選ばれているツールバーを初期状態に戻す\n(他のツールバーには影響ありません)
    {StringPatchType::Push, 0x4D76A0 + 0xEB, "Reverts this toolbar to default configuration\n(Other toolbars are not affected)"},

    // 全てのコマンド
    {StringPatchType::Push, 0x4D7860 + 0x116, "All Commands"},

    // ボタン以外のパーツ
    {StringPatchType::Push, 0x4D7860 + 0x101, "Miscellaneous"},

    // （空白）
    {StringPatchType::Push, 0x4D79C0 + 0x84, "(space)"},
    {StringPatchType::Push, 0x4D8230 + 0x6E, "(space)"},

    // 空白です。ボタンの位置調整にご利用ください。
    {StringPatchType::Push, 0x4D7CE0 + 0xCD, "Adds a blank space in between commands."},

    // ツールバーにはツールボタンが最低１つは必要です。
    {StringPatchType::Push, 0x4D88D0 + 0xA6, "At least one command/control is required for each toolbar."},

    // ツールバーカスタマイズ
    {StringPatchType::Push, 0x4D8B98, "Toolbar Customization"},

    // ツールバーの名前を入力してください。
    {StringPatchType::Push, 0x4D8B7F, "Input a name for this toolbar."},

    // ツールバー名(&N)
    {StringPatchType::Push, 0x4D8B66, "&Name:"},

    // トラックバー
    {StringPatchType::Push, 0x4DAE50 + 0x9, "Track Bar"},

    // カレントトラック
    {StringPatchType::Push, 0x4DB760 + 0x6, "Tracklist Box"},

    // 選択 (Tr.%d, %s) → (Tr.%d, %s)
    {StringPatchType::Push, 0x4E21C0 + 0x70, "Selection from (Tr.%d, %s) >> (Tr.%d, %s)"},

    // トラックリスト - 選択ツール
    {StringPatchType::Push, 0x4E2640 + 0x6, "Tracklist - Select Tool"},

    // ピアノロールへ切り替え
    {StringPatchType::Push, 0x4E3610 + 0x110, "Switch to track's Piano Roll"},

    // トラックモニターバー
    {StringPatchType::Push, 0x4E3D10 + 0x1E, "Track Monitor Bar"},

    // パーツが多すぎです。
    {StringPatchType::Push, 0x4E54B0 + 0x55, "Maximum panels exceeded."},

    // １つ以上のパーツが必要です。
    {StringPatchType::Push, 0x4E54B0 + 0x2E, "At least 1 panel is required."},

    // 音色
    {StringPatchType::Push, 0x4E6BC0 + 0x6, "Patch"},

    // 鍵盤
    {StringPatchType::Push, 0x4E77C0 + 0x6, "Keyboard"},

    // ピッチベンド
    {StringPatchType::Push, 0x4E8910 + 0x6, "Pitch Bend"},

    // ベロシティメーター
    {StringPatchType::Push, 0x4E9030 + 0x6, "Velocity Meter"},

    // 自動
    {StringPatchType::Push, 0x4EC513, "Auto"},

    // イベントグラフ2
    {StringPatchType::Push, 0x4EEC10 + 0x2A9, "Graph Panel 2"},

    // イベントグラフ1
    {StringPatchType::Push, 0x4EEC10 + 0x26B, "Graph Panel 1"},

    // 指定した直線・曲線を使う
    {StringPatchType::Push, 0x4F11F8, "(empty)"},

    // 処理しない
    {StringPatchType::Push, 0x4F37AF, "Not set"},

    // 処理する
    {StringPatchType::Push, 0x4F37A8, "Utilized"},

    // %d小節以降を処理する
    {StringPatchType::Push, 0x4F3750 + 0x48, "Utilized from measure %d"},

    // 設定
    {StringPatchType::Push, 0x4F3910 + 0xAA, "Profile"},

    // トラック
    {StringPatchType::Push, 0x4F3910 + 0x97, "Track"},

    // 完全8度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0x125, "P8/A7", 0x80 - 0x40},

    // 長7度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0x11D, "M7/d8", 0x80 - 0x44},

    // 短7度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0x115, "m7/A6", 0x80 - 0x48},

    // 長6度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0x10D, "M6/d7", 0x80 - 0x4C},

    // 短6度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0x105, "m6/A5", 0x80 - 0x50},

    // 完全5度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0xFD, "P5/d6", 0x80 - 0x54},

    // 増4度/減5度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0xF5, "d5/A4 (tritone)", 0x80 - 0x58},

    // 完全4度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0xED, "P4/A3", 0x80 - 0x5C},

    // 長3度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0xE5, "M3/d4", 0x80 - 0x60},

    // 短3度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0xDD, "m3/A2", 0x80 - 0x64},

    // 長2度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0xD5, "M2/d3 (tone)", 0x80 - 0x68},

    // 短2度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0xCD, "m2/A1 (semitone)", 0x80 - 0x6C},

    // 完全1度
    {StringPatchType::MovPtrESP, 0x4F4120 + 0xC5, "P1/d2", 0x80 - 0x70},

    // 16進数の書式が間違っています。
    {StringPatchType::Push, 0x4F5D50 + 0xB0, "Invalid hexadecimal format."},

    // このパレットタイプには対応していません。
    {StringPatchType::Push, 0x4F60B0 + 0x165, "This palette type is not supported."},

    // 色数が多すぎます。
    {StringPatchType::Push, 0x4F60B0 + 0x129, "Too many colors!"},

    // PNG構造体を初期化出来ませんでした。
    {StringPatchType::Push, 0x4F60B0 + 0xB4, "Could not initialize PNG structure."},

    // PNG構造体を作成出来ませんでした。
    {StringPatchType::Push, 0x4F60B0 + 0x82, "Could not write PNG structure."},

    // ファイルをオープン出来ませんでした。\n\n%s
    {StringPatchType::Push, 0x4F60B0 + 0x4A, "Could not open the following:\n\n%s"},

    // 指定したオブジェクトを表示
    {StringPatchType::MovPtrESP, 0x4F6760 + 0x7D, "Display specified object", 0x24 - 0x18},

    // ファイルの読み込みに失敗しました : %s
    {StringPatchType::Push, 0x4F7130 + 0x44, "Failed to load file. (%s)"},

    // デフォルトベロシティ
    {StringPatchType::Push, 0x4F8C50 + 0x6, "Default Velocity Box"},

    // 原因不明のエラーが発生しました。\n\n読み込みを中断します。
    {StringPatchType::Push, 0x4F9899, "An unknown error has occurred.\n\nThe operation was aborted."},

    // ファイルの読み込みに失敗しました。\n
    {StringPatchType::Push, 0x4F9700 + 0x62, "Failed to load file.\n\n"},
    {StringPatchType::Push, 0x4F9700 + 0xD2, "Failed to load file.\n\n"},

    // 属性の解析に失敗しました。\n\nタグ : %s\n行数 : %d
    {StringPatchType::Push, 0x4F98F0 + 0x51C, "Failed to parse attributes.\n\nTag: %s\nLine: %d"},
    {StringPatchType::Push, 0x4F98F0 + 0x561, "Failed to parse attributes.\n\nTag: %s\nLine: %d"},
    {StringPatchType::Push, 0x4F98F0 + 0x5A3, "Failed to parse attributes.\n\nTag: %s\nLine: %d"},

    // コメントの閉じタグが見つかりません。\n\n行数 : %d
    {StringPatchType::Push, 0x4F98F0 + 0x42D, "Missing comment closing tag.\n\nLine: %d"},

    // 閉じるタグが見つかりません。\n\nタグ : %s\n行数 : %d
    {StringPatchType::Push, 0x4F98F0 + 0x400, "Missing closing tag.\n\nTag: %s\nLine: %d"},
    {StringPatchType::Push, 0x4F98F0 + 0x4C0, "Missing closing tag.\n\nTag: %s\nLine: %d"},

};