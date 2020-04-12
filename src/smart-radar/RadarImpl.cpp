#include "RadarImpl.h"

RadarImpl::RadarImpl(int servoPin, int sonarPin, int trigPin, int potPin) {
  this->servo = new ServoMotorImpl(servoPin);
  this->sonar = new Sonar(sonarPin, trigPin);
  this->pot = new Potentiometer(potPin);
  servo->on();
  scanningTime = mapScanningValue(pot->getValue());
  init();
}

/* move the servo to 0 radius and set the amount with a positive value */
void RadarImpl::init() {
  radiusAmount = INTERVAL_RADIUS;
  servo->setPosition(0);
}

float RadarImpl::getScanDistance() {
  return sonar->getDistance();
}

int RadarImpl::getPosition() {
  return servo->getPosition();
}

int RadarImpl::getScanningTime() {
  return scanningTime;
}

void RadarImpl::autoMove() {
  servo->setPosition(getPosition()+radiusAmount);
  int pos = getPosition();
  if(pos == 0 || pos == 180) {
    radiusAmount = -radiusAmount;
  }
}

void RadarImpl::moveOfAmount(int amount) {
  float newPos = getPosition() + INTERVAL_RADIUS * amount;
  if(newPos <= 180 && newPos >= 0) {
    servo->setPosition(newPos);  
  }
}

void RadarImpl::updateScanningTime(int amount) {
  if(!isScanningTimeChanged()) {
    int currValue = scanningTime + amount * BASE_SCAN_TIME;
    if(currValue >= MIN_SCAN_TIME && currValue <= MAX_SCAN_TIME) {
      scanningTime = currValue;
    }
  }
}

bool RadarImpl::isScanningTimeChanged() {
  int lastValue = mapScanningValue(pot->getValue());
  pot->updateValue();
  int currValue = mapScanningValue(pot->getValue());
  if(currValue != lastValue) {
     scanningTime = currValue;
  } 
}
