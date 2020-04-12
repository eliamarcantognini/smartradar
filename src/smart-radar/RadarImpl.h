#ifndef __RADAR_IMP__
#define __RADAR_IMP__

#include "Radar.h"

/* Time multiplier for each scan interval */
#define BASE_SCAN_TIME 100
#define INTERVAL_RADIUS 12
#define MAX_SCAN_TIME 600
#define MIN_SCAN_TIME 200

class RadarImpl: public Radar {

  public:
    RadarImpl(int servoPin, int sonarPin, int trigPin, int potPin);

    float getScanDistance();
    int   getPosition();
    int   getScanningTime();
    void  updateScanningTime(int amount);
    void  moveOfAmount(int amount);
    void  autoMove();
    void  init();

  private:
    ServoMotor* servo;
    Sonar* sonar;
    Potentiometer* pot;
    int radiusAmount;
    int scanningTime;

    int mapScanningValue(int value) {
      return map(value, 0, 1023, 2, 6) * BASE_SCAN_TIME;
    }

    bool isScanningTimeChanged();
};

#endif
