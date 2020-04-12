#ifndef __AUTO_MODE_TASK__
#define __AUTO_MODE_TASK__

#include "AbstractRadarTask.h"

#define D_NEAR 0.2
#define D_FAR 0.4

class AutoModeTask: public AbstractRadarTask {
  private:

    enum { SCANNING, MOVING, TRACKING, RESET } state;

    bool isRangeAlarm(float distance);
    bool hasToTrack(float distance);

  public:
    
    AutoModeTask(Radar* radar, StateManager* sManager, UserConsole* console);
    void init(int period);     
    void tick();
};
#endif
