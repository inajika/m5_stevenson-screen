#ifndef HUMIDITYINDEX_H
#define HUMIDITYINDEX_H

// 不快指数
class HumidityIndex {
  public:
    HumidityIndex() {}
    float calc(float cTemp, float humidity);
};

#endif