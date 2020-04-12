#ifndef __BLINKING_TASK__
#define __BLINKING_TASK__

#include "Task.h"
#include "Led.h"
#include "StateManager.h"
#include "UserConsole.h"

class BlinkingTask: public Task {
  private:

    enum { OFF, BLINK_ON, ALARM_ON } state;

    Light* alarmLed;
    Light* blinkLed;
    StateManager* sManager;
    UserConsole* console;
  
  public: 

    BlinkingTask(int alarmPin, int blinkLed, StateManager* sManager, UserConsole* console);
    void init(int period);
    void tick();
}; 

#endif
