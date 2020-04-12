#include "AutoModeTask.h"

AutoModeTask::AutoModeTask(Radar* radar, StateManager* sManager, UserConsole* console)
: AbstractRadarTask(radar, sManager, console) {
}

void AutoModeTask::init(int period) {
    Task::init(period);
    state = SCANNING;
}

void AutoModeTask::tick() {
  switch(state) {
    case SCANNING: {
      if(getStateManager()->isModeChanging()) {
        state = RESET;
      } else {
        float dist = getRadar()->getScanDistance();
        getConsole()->displayObjectDistance(dist);
        getConsole()->displayServoDirection(getRadar()->getPosition());
        updateScanTime(getConsole()->rcvFrequency());
        if(hasToTrack(dist)) {
          state = TRACKING;
          getStateManager()->setAlarm(true);
        } else {
          getStateManager()->setAlarm(isRangeAlarm(dist));
          state = MOVING;
        }
      }
      break;
    }
    case TRACKING: {
      float dist = getRadar()->getScanDistance();
      getConsole()->displayObjectDistance(dist);
      if(getStateManager()->isModeChanging()) {
        state = RESET;
      } else if(!hasToTrack(dist)) {
        state = SCANNING;
        getStateManager()->setAlarm(false);
      }
      break;
    }
    case MOVING: {
      updateScanTime(getConsole()->rcvFrequency());
      if(getStateManager()->isModeChanging()) {
        state = RESET;
      } else if(isTimeToMove()) {
        getRadar()->autoMove();
        state = SCANNING;
      }
      break;
    }
    case RESET: {
      reset();
      getStateManager()->setAlarm(false);
      state = SCANNING;
      disable();
      break;
    }
  }
}

bool AutoModeTask::isRangeAlarm(float distance) {
  return distance >= D_NEAR && distance <= D_FAR;
}

bool AutoModeTask::hasToTrack(float distance) {
  return distance > 0 && distance < D_NEAR;
}
