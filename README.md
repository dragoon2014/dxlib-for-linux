DxLib for Linux
===============

DXライブラリをLinuxでも動作するように移植してみました。

# 使用方法
```
# 必要なパッケージを取得します。APT を用いないシステムでは、等価なものを適切な方法で取得してください。
sudo apt install git g++ unzip make wget libtiff-dev libopenal-dev libvorbis-dev libopusfile-dev libtheora-dev

# 以下でライブラリがDxLibMake/libDxLib.aに生成されます。
# サンプルもあわせてsamples以下に生成されます。
# 初回実行時にはDXライブラリのソースをダウンロードするのでオンラインである必要があります。
make patch
make -j4

# 以下で実行ファイルを生成できます。
# 細かいパラメータはMakefile内のサンプルを生成する箇所を参考にしてください。
gcc -o 実行ファイル ソース.cpp \
    -I DxLibMakeのパス -DDX_NON_〜(必要なdefine) \
    -I insufficient_include(ほか必要なinclude) \
    DxLibMake/libDxLib.a -lEGL ...(必要なライブラリ)... -lz
```

# 利用できる機能

用語は[関数リファレンスページ](https://dxlib.xsrv.jp/dxfunc.html)

## 動作する

- 使用必須関数
- 図形描画関数
  - DrawTriangle(with TransFlag=FALSE)だけ動作がおかしいかもしれない
- 簡易画面出力関数
- 入力関係の関数
  - マウスとキーボードのみ

## 一部動作を確認

- グラフィックデータ制御関数
- 文字描画関係関数
- 音利用関数
- ３Ｄ関係関数
- その他画面操作系関数

## 未確認

- マスク関係関数
- 動画関係関数
- 音楽再生関数
- ウエイト関係の関数
- 時間関係の関数
- 乱数取得関数
- ウインドウモード関係
- ドット単位で画像にアクセスしたい関係
- 非同期読み込み関係
- 文字関係関数
- マイナー関数
- ファイル読み込み関係
- 通信関係

## 動作しない

- Live2D関係関数
- ３Ｄ関係関数のうちBulletを利用している関数

# 動作確認環境

Xubuntu 20.04
他ディストリビューションでも動くと思います。

# リポジトリ自体のライセンス

独自部分はMITライセンスで提供されます、LICENSEファイルを参照してください。

一部、手動および自動変換されたDXライブラリのコードが含まれています。

DX Library Copyright (C) 2001-2019 Takumi Yamada.

また、依存関係の都合でVorbisのヘッダーファイルが含まれています。

insufficient\_include/COPYING-vorbis.txtを参照してください。

samples/assetsディレクトリ内の素材についてはASSETS\_README.txtを参照してください。
