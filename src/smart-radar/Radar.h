#ifndef __RADAR__
#define __RADAR__

#include "ServoMotorImpl.h"
#include "Sonar.h"
#include "Potentiometer.h"

class Radar {
  public:
    
    virtual int   getPosition() = 0;
    virtual int   getScanningTime() = 0;
    virtual void  init() = 0;
    virtual void  updateScanningTime(int amount) = 0;
    virtual void  moveOfAmount(int amount) = 0;
    virtual void  autoMove() = 0;
    virtual float getScanDistance() = 0;  
    
};

#endif
