#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
  updateValue();
} 
  
float Potentiometer::getValue(){
  return value;
}

void Potentiometer::updateValue() {
  value = analogRead(pin);
}
