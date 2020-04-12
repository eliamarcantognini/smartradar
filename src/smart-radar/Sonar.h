#ifndef __SONAR__
#define __SONAR__

#include "ProximitySensor.h"

#define MAX_RANGE 5

class Sonar: public ProximitySensor {

public:  
    Sonar(int echoPin, int trigPin);
    float getDistance();
  
private:
    const double vs = 331.45 + 0.62*20;
    int echoPin, trigPin;
};

#endif 
