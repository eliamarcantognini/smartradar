#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

class Potentiometer {
 
public: 
  Potentiometer(int pin);
  
  float getValue();
  void  updateValue();

private:
  int pin;
  float value;

};

#endif
