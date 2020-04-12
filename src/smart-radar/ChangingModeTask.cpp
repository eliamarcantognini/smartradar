#include "ChangingModeTask.h"

ChangingModeTask::ChangingModeTask(int autoPin, int singlePin, int manualPin, StateManager* sManager, 
UserConsole* console, Task* autoT, Task* singleT, Task* manualT) {
  this->sManager = sManager;
  this->console = console;
  tasks[AUTO] = autoT;
  tasks[SINGLE] = singleT;
  tasks[MANUAL] = manualT;
  buttons[AUTO]   = new ButtonImpl(autoPin);
  buttons[SINGLE] = new ButtonImpl(singlePin);
  buttons[MANUAL] = new ButtonImpl(manualPin);
  changingTime = 0;
}

void ChangingModeTask::init(int period) {
  Task::init(period);
  state = CHECKING;
  modToBeSet = Mod(-1);
  sManager->setModality(MANUAL);
}

void ChangingModeTask::tick() {
  switch(state) {
    case CHECKING: {
      console->checkMessage();
      if(isModeChanged()) {
        state = CHANGING;
        sManager->setModeChanging(true);
      } 
      break;
    }
    case CHANGING: {
      changingTime += getPeriod(); 
      if(changingTime >= CHANGING_TIME) {
        state = CHECKING;
        changingTime = 0;
        sManager->setModeChanging(false);
        sManager->setModality(modToBeSet);
        tasks[modToBeSet]->enable();
        console->displayModality(modToBeSet);
      }
      break;
    }
  }
}

bool ChangingModeTask::isModeChanged() {
  return checkButtons() || checkConsole();
}

bool ChangingModeTask::checkButtons() {
  for(int mod = 0; mod < BTN_NUM; mod++) {
    if(sManager->getModality() != Mod(mod) && buttons[mod]->isPressed()) {
      modToBeSet = Mod(mod);
      return true;
    }
  }
  return false;
}

bool ChangingModeTask::checkConsole() {
  Mod consoleMod = console->rcvModality();
  if(consoleMod > -1 && consoleMod != sManager->getModality()) {
    modToBeSet = consoleMod;
    return true;
  }
  return false;
}
