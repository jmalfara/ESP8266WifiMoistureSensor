#ifndef DebugMode_h
#define DebugMode_h
#include "Arduino.h"
#include "OneButton/OneButton.h"
#include "MoistureSensor.h"
#define RED 15
#define GREEN 12
#define BLUE 13

extern "C" {
#include "user_interface.h"
}

class DebugMode {
  public:
    static void startDebug(int zone, int id, int button, MoistureSensor *sensor);
    static void flash(int pin, int delayTime);
  private:
    static MoistureSensor *_sensor;
    static int _zone;
    static int _id;
    static void longClick();
    static void doubleClick();
    static void singleClick();
};

#endif
