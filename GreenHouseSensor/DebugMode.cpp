#include "DebugMode.h"
int DebugMode::_id = -1;
int DebugMode::_zone = -1;
MoistureSensor * DebugMode::_sensor = NULL;

void DebugMode::startDebug(int zone, int id, int buttonPin, MoistureSensor *sensor) {
  _sensor = sensor;
  _zone = zone;
  _id = id;
  OneButton button(buttonPin, 1);
  button.attachDoubleClick(doubleClick);
  button.attachClick(singleClick);
  button.attachLongPressStart(longClick);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  if (digitalRead(buttonPin) == 0) {
    flash(RED, 500);
    while(true) {
      delay(100);
      button.tick();
    }
  }
}

//Connection Status
void DebugMode::singleClick() {
  Serial.println("Single Clicked");
  flash(GREEN, 500);
  system_restart();
}

// Zone/ID info
void DebugMode::doubleClick() {
  // Flash Zone
  Serial.println("Double Clicked");
  for (int i = 0; i < _zone; i++) {
    flash(BLUE, 500);
  }

  // Flash Id
  for (int i = 0; i < _id; i++) {
    flash(GREEN, 500);
  }
}

//Start Sensor Calibration
void DebugMode::longClick() {
  Serial.println("Long Clicked");
  Serial.println("Starting Calibration");
  flash(BLUE, 500);
  flash(BLUE, 500);
  flash(BLUE, 500);

  // Dry Rating
  flash(RED, 500);
  _sensor->setFullDry();

  flash(BLUE, 500);
  flash(BLUE, 500);
  flash(BLUE, 500);

  // Dry Rating
  flash(RED, 500);
  _sensor->setFullWet();

  flash(GREEN, 500);
  Serial.println("Stored In EEPROM");
  _sensor->setEEPROM();
}

void DebugMode::flash(int pin, int delayTime) {
  digitalWrite(pin, HIGH);
  delay(delayTime);
  digitalWrite(pin, LOW);
  delay(delayTime);
}

