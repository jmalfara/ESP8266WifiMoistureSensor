#include "MoistureSensor.h"

MoistureSensor::MoistureSensor(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

void MoistureSensor::setFullDry() {
  int total = 0;
  for (int i = 0; i < SAMPLE; i++) {
    total += analogRead(_pin);
  }
  data.dry = total/SAMPLE;
  Serial.println(data.dry);
}

void MoistureSensor::setFullWet() {
  int total = 0;
  for (int i = 0; i < SAMPLE; i++) {
    total += analogRead(_pin);
  }
  data.wet = total/SAMPLE;
  Serial.println(data.wet);
  
}

float MoistureSensor::getReading() {
  int total = 0;
  for (int i = 0; i < SAMPLE; i++) {
    total += analogRead(_pin);
  }
  return total/SAMPLE;
}

int MoistureSensor::getPercent() {
  float baseLine = data.wet - data.dry;
  float reading = getReading();
  return (int)(((reading - data.dry) / baseLine) * 100);
}

void MoistureSensor::setEEPROM() {
  EEPROM.begin(sizeof(SensorData));
  EEPROM.put(0, data);
  Serial.println(data.wet);
  Serial.println(data.dry);
  EEPROM.commit();
  EEPROM.end();
}

void MoistureSensor::getEEPROM() {
  EEPROM.begin(sizeof(SensorData));
  EEPROM.get(0, data);
  EEPROM.commit();
  EEPROM.end();
}
