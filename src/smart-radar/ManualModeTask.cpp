#include "ManualModeTask.h"

ManualModeTask::ManualModeTask(Radar* radar, StateManager* sManager, UserConsole* console)
: AbstractRadarTask(radar, sManager, console) {
}

void ManualModeTask::init(int period) {
    Task::init(period);
    state = SCANNING;
}

void ManualModeTask::tick() {
  switch(state) {
    case SCANNING: {
      if(getStateManager()->isModeChanging()) {
        state = RESET;
      } else {
        getConsole()->displayObjectDistance(getRadar()->getScanDistance());
        getConsole()->displayServoDirection(getRadar()->getPosition());
        state = MOVING;
      }
      break;
    }
    case MOVING: {
      if(getStateManager()->isModeChanging()) {
        state = RESET;
      } else {
        getRadar()->moveOfAmount(getConsole()->rcvDirection());
        state = SCANNING;
      }
      break;
    }
    case RESET: {
      reset();
      state = SCANNING;
      disable();
      break;
    }
  }
}
