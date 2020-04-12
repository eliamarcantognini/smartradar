#include "SingleModeTask.h"
#include <avr/sleep.h>

volatile bool isDetected = false;

void wakeUp() {
  isDetected = true;
}

SingleModeTask::SingleModeTask(Pir* pir, Radar* radar, StateManager* sManager, UserConsole* console)
: AbstractRadarTask(radar, sManager, console) {
  this->pir = pir;
}

void SingleModeTask::init(int period) {
    Task::init(period);
    pir->calibrate();
    state = PIR_SCANNING;
}

void SingleModeTask::tick() {
  switch(state) {
    case PIR_SCANNING: {
      enterOnPowerSaveMode();
      if(isDetected) {
        isDetected = false;
        getConsole()->displaySaveMode(false);
        state = SONAR_SCANNING;
      }
      break;
    }
    case SONAR_SCANNING: {
      if(getStateManager()->isModeChanging()) {
        state = RESET;
      } else {
        float dist = getRadar()->getScanDistance();
        getConsole()->displayObjectDistance(dist);
        getConsole()->displayServoDirection(getRadar()->getPosition());
        updateScanTime(getConsole()->rcvFrequency());
        if(dist > 0 && dist < D_FAR) {
          getStateManager()->setBlinking(true);
        }
        state = MOVING; 
      }
      break;
    }
    case MOVING: {
      updateScanTime(getConsole()->rcvFrequency());
      if(getStateManager()->isModeChanging()) {
        state = RESET;
      } else if(isTimeToMove()) {
        getRadar()->autoMove();
        state = SONAR_SCANNING;
        checkScanEnd();
      }
      break;
    }
    case RESET: {
      reset();
      state = PIR_SCANNING;
      disable();
      break;
    }
  }
}

void SingleModeTask::checkScanEnd() {
  int pos = getRadar()->getPosition();
  if(pos == 180 || pos == 0) {
   state = PIR_SCANNING;
  }
}

void SingleModeTask::enterOnPowerSaveMode() {      
  getConsole()->displaySaveMode(true);
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, RISING);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  delay(30);
  sleep_mode();
  // Wake up here
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(2));
}
