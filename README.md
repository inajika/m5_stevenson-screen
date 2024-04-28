# M5百葉箱
**このプログラムは、個人が作成した非公式プログラムです。**

このプログラムを動作させるには、以下の機器が必要です。
- 動作確認済みのM5Stackシリーズ本体
- M5Stack用温湿度気圧センサユニット Ver.4(ENV Ⅳ)

また、`include/config.sample.h`をコピーして同じ階層に`config.h`を作成してください。

## 機能
気温(摂氏)、湿度(%)、不快指数、現地気圧(hPa)、観測高度(m)、海面気圧(hPa)、Wi-Fi接続情報を画面に表示します。

Wi-Fiに接続するには`include/config.h`にSSID、パスワードを設定する必要があります。

## 動作確認済みのM5Stackシリーズ
- M5Stack GRAY Development Kit
  - `env:m5stack-gray`
- AtomS3
  - `env:m5stack-atoms3`
- M5Paper(センサはPORT. Aに接続してください)
  - `env:m5stack-fire`

## 設定項目
### `INTERVAL_TO_OBSERVE_MS`(観測間隔、整数値)
気温、湿度、不快指数、観測高度、現地/海面気圧の観測間隔をミリ秒で設定します

### `WIFI_SSID`(Wi-FiルータSSID、文字列)
接続したいWi-FiルータのSSIDを設定します

### `WIFI_PASSWORD`(Wi-Fiパスワード、文字列)
Wi-Fiに接続するためのパスワードを設定します

### `WIFI_CONNENTION_ATTEMPT_LIMIT`(Wi-Fi接続リトライ回数の上限、整数値)
Wi-Fiへの接続をリトライする回数を設定します

環境に応じて調整してください

## ライセンス
[MIT](/LICENSE)