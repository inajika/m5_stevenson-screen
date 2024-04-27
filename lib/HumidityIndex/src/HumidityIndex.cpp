#include <HumidityIndex.h>

// 不快指数を計算
float HumidityIndex::calc(float cTemp, float humidity) {
  return 0.81 * cTemp + 0.01 * humidity * (0.99 * cTemp - 14.3) + 46.3;
}