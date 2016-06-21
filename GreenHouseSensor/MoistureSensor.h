#ifndef MoistureSensor_h
#define MoistureSensor_h
#define SAMPLE 100

#include "Arduino.h"
#include <EEPROM.h>

typedef struct {
  float dry;
  float wet;
} SensorData;

class MoistureSensor {
  public:
    MoistureSensor(int pin);
    void setFullDry();
    void setFullWet();
    int getPercent();
    void setEEPROM();
    void getEEPROM();
  private:
    float getReading();
    int _pin;
    SensorData data;
};

#endif
