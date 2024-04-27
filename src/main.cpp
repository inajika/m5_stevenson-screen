#include <M5Unified.h>
#include <M5UnitENV.h>
#include <HumidityIndex.h>

SHT4X sht4;
BMP280 bmp;

HumidityIndex humidIdx;

// 計測データ
struct MeasuredData {
  float cTemp; // 気温(摂氏)
  float humidity; // 湿度(%)
  float barometric; // 気圧(Pa)
  float altitude; // 高度(m)
};
MeasuredData data;

// データ表示
void displayData() {
  M5.Display.setCursor(0, 0);
  M5.Display.startWrite();
  M5.Display.fillScreen(M5.Display.isEPD() ? TFT_WHITE : TFT_BLACK);
  
  // データ表示
  // 気温(摂氏)
  M5.Display.print("気温: ");
  M5.Display.print(data.cTemp);
  M5.Display.println("℃");

  // 湿度(%)
  M5.Display.print("湿度: ");
  M5.Display.print(data.humidity);
  M5.Display.println("%");

  // 気圧(hPa)
  M5.Display.print("気圧: ");
  M5.Display.print(data.barometric / 100);
  M5.Display.println("hPa");

  // 高度(m)
  M5.Display.print("高度: ");
  M5.Display.print(data.altitude);
  M5.Display.println("m");

  // 不快指数
  M5.Display.print("不快指数: ");
  M5.Display.println(humidIdx.calc(data.cTemp, data.humidity));

  M5.Display.endWrite();
}

void setup() {
  auto config = M5.config();
  M5.begin(config);

  switch (M5.getBoard()) {
    case m5::board_t::board_M5AtomS3:
      // AtomS3
      M5.Display.setFont(&fonts::lgfxJapanGothic_12);
      M5.Display.setTextSize(1.4);
      break;
    default:
      break;
  }

  // You can have 3 different precisions, higher precision takes longer
  if (!sht4.begin(&Wire, SHT40_I2C_ADDR_44, m5::Ex_I2C.getSDA(), m5::Ex_I2C.getSCL(), 400000U)) {
    M5.Display.println("Couldn't find SHT4x");
    while (1) delay(1);
  }

  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  sht4.setHeater(SHT4X_NO_HEATER);

  if (!bmp.begin(&Wire, BMP280_I2C_ADDR, m5::Ex_I2C.getSDA(), m5::Ex_I2C.getSCL(), 400000U)) {
    M5.Display.println("Couldn't find BMP280");
    while (1) delay(1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(BMP280::MODE_NORMAL,     /* Operating Mode. */
                  BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  BMP280::FILTER_X16,      /* Filtering. */
                  BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  if (sht4.update()) {
    data.cTemp = sht4.cTemp;
    data.humidity = sht4.humidity;
  } else {
    data.cTemp = 0.0f;
    data.humidity = 0.0f;
  }

  if (bmp.update()) {
    if (data.cTemp == 0.0f) {
      data.cTemp = bmp.readTemperature();
    }
    data.barometric = bmp.readPressure();
    data.altitude = bmp.readAltitude();
  } else {
    data.barometric = 0.0f;
    data.altitude = 0.0f;
  }

  displayData();
  delay(1000);
}
