#ifndef Compass_H
#define Compass_H

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include <Wire.h>
#include <Arduino.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

class Compass {
  public:
    Compass();
    void initializeIMU();
    float getHeading();
  private:
    Adafruit_BNO055 myIMU;
};

#endif
