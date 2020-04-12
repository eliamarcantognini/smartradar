#ifndef __MANUAL_MODE_TASK__
#define __MANUAL_MODE_TASK__

#include "AbstractRadarTask.h"
#include "UserConsole.h"

class ManualModeTask: public AbstractRadarTask {
  private:

    enum { SCANNING, MOVING, RESET } state;
    
  public:
    
    ManualModeTask(Radar* radar, StateManager* sManager, UserConsole* console);
    void init(int period);     
    void tick();
};
#endif
