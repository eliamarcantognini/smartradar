#ifndef __ABSTRACT_RADAR_TASK__
#define __ABSTRACT_RADAR_TASK__

#include "Task.h"
#include "StateManager.h"
#include "Radar.h"
#include "UserConsole.h"

class AbstractRadarTask: public Task{
  private:

    StateManager* sManager;
    Radar* radar;
    UserConsole* console;
    long scanningTime;

  protected:
    StateManager* getStateManager() {
      return sManager;
    }

    Radar* getRadar() {
      return radar;
    }

    UserConsole* getConsole() {
      return console;
    }

  public:
  
    virtual void init(int period);
    
    virtual void tick();
    
    AbstractRadarTask(Radar* radar, StateManager* sManager, UserConsole* console) {
      this->sManager = sManager;
      this->radar = radar;
      this->scanningTime = 0;
      this->console = console;
    }

    void reset() {
      scanningTime = 0;
      radar->init();
    }

    void updateScanTime(int amount) {
      radar->updateScanningTime(amount);
      scanningTime += getPeriod();
    }

    bool isTimeToMove() {
      if(scanningTime >= radar->getScanningTime()) {
          scanningTime = 0;
          return true;
      } 
      return false;
    }


};
#endif
