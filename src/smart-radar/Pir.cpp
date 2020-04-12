#include "Pir.h"
#include "Arduino.h"

#define CALIBRATION_TIME_MS 10000

Pir::Pir(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);     
} 
  
bool Pir::isDetected() {
  return digitalRead(pin) == HIGH;
}

void Pir::calibrate() {
  delay(CALIBRATION_TIME_MS);
}
