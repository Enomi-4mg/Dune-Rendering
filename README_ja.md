# Dune-Rendering

[🇬🇧 English](README.md)

## 概要

Dune-RenderingはopenFrameworksを使用して構築されたインタラクティブなビジュアライゼーションプロジェクトです。砂漠と砂丘のリアルタイムレンダリングで素晴らしい映像を作成します。

## 特徴

- 砂漠風景の3Dリアルタイムレンダリング
- インタラクティブなカメラコントロール
- 高度なビジュアルエフェクト用のカスタムGLSLシェーダ
- openFrameworksフレームワークを使用したOpenGLベースのグラフィックス

## プロジェクト構造

```
src/
  ├── main.cpp          # エントリーポイント
  ├── ofApp.cpp         # アプリケーション実装
  └── ofApp.h           # アプリケーションヘッダ

bin/
  └── data/
      ├── shader.vert   # 頂点シェーダ
      └── shader.frag   # フラグメントシェーダ

config.make            # ビルド設定
addons.make            # openFrameworksアドオン
```

## 必要要件

- Visual Studio 2022以降
- openFrameworks v0.12.1
- Windows x64プラットフォーム

## ビルド方法

1. Visual Studioで`Dune_Rendering.sln`を開く
2. ソリューションをビルド（DebugまたはRelease設定）
3. `bin/`ディレクトリから実行ファイルを実行

## シェーダ

プロジェクトは`bin/data/`に配置されたカスタムGLSLシェーダを使用しています：
- `shader.vert` - 幾何学的変換用の頂点シェーダ
- `shader.frag` - ピクセルレベルのエフェクト用のフラグメントシェーダ

## ライセンス

詳細は[LICENSE](LICENSE)ファイルを参照してください。

## 作成者

openFrameworksレンダリング実験として作成されました。