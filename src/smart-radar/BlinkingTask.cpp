#include "BlinkingTask.h"

BlinkingTask::BlinkingTask(int alarmPin, int blinkPin, StateManager* sManager, 
UserConsole* console) { 
  this->alarmLed = new Led(alarmPin);
  this->blinkLed = new Led(blinkPin);
  this->sManager = sManager;
  this->console = console;
}

void BlinkingTask::init(int period) {
  Task::init(period);
  state = OFF;
}

void BlinkingTask::tick() {
  switch(state) {
    case OFF: {
      if (sManager->hasToBlink()) {
        blinkLed->switchOn();
        //console->displayAlarm(true);
        state = BLINK_ON;
      } else if(sManager->isOnAlarm()) {
        alarmLed->switchOn();
        console->displayAlarm(true);
        state = ALARM_ON;
      }
      break;
    }
    case ALARM_ON: {
      alarmLed->switchOff();
      console->displayAlarm(false);
      state = OFF;
      break;
    } 
    case BLINK_ON: {
      blinkLed->switchOff();
      sManager->setBlinking(false);
      state = OFF;
      break;
    }
  } 
} 
