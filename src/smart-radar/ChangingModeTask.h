#ifndef __CHANGING_MODE_TASK__
#define __CHANGING_MODE_TASK__

#include "Arduino.h"
#include "Task.h"
#include "StateManager.h"
#include "ButtonImpl.h"
#include "UserConsole.h"

#define CHANGING_TIME 1500
#define BTN_NUM 3
#define MODE_NUM 3

class ChangingModeTask: public Task {
  private:

    enum { CHECKING, CHANGING } state;

    Task* tasks[MODE_NUM];
    Button* buttons[BTN_NUM];
    StateManager* sManager;
    long changingTime;
    Mod modToBeSet;
    UserConsole* console;
    bool isModeChanged();
    bool checkButtons();
    bool checkConsole();

  public:

    ChangingModeTask(int autoPin, int singlePin, int manualPin, StateManager* sManager, UserConsole* console,
                      Task* autoT, Task* singleT, Task* manualT);
    void init(int period);
    void tick();
};

#endif
