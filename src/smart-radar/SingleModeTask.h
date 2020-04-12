#ifndef __SINGLE_MODE_TASK__
#define __SINGLE_MODE_TASK__

#include "AbstractRadarTask.h"
#include "Pir.h"

#define D_FAR 0.4

class SingleModeTask: public AbstractRadarTask {
  private:

    enum { PIR_SCANNING, SONAR_SCANNING, MOVING, RESET } state;
    Pir* pir;

    void checkScanEnd();
    void enterOnPowerSaveMode();

  public:
    
    SingleModeTask(Pir* pir, Radar* radar, StateManager* sManager, UserConsole* console);
    void init(int period);     
    void tick();
};
#endif
