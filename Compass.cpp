#include "Compass.h"

Compass::Compass() : myIMU(Adafruit_BNO055()) {}

void Compass::initializeIMU() {
  if (!myIMU.begin()) {
    Serial.println("BNO055 not detected!");
    while (1);
  }
  delay(1000);
  myIMU.setExtCrystalUse(true);
}

float Compass::getHeading() {
  imu::Vector<3> euler = myIMU.getVector(Adafruit_BNO055::VECTOR_EULER);
  float heading_deg = euler.x();
  if (heading_deg < 0) heading_deg += 360;
  delay(BNO055_SAMPLERATE_DELAY_MS);
  return heading_deg;
}
