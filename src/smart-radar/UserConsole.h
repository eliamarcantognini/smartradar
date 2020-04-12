#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__

#include "MsgService.h"
#include "StateManager.h"


const String prefix = "sr:";

class UserConsole {
  private:

    Msg* lastMsg;
    int direction;
    Mod mode;
    int frequency;
    void reset(char param);
  
  public:
  
    UserConsole();
    void displayModality(Mod modality);
    void displayServoDirection(int dir);
    void displaySaveMode(bool on);
    void displayAlarm(bool on);
    void displayObjectDistance(float pos);
    void displayReady();
    int rcvDirection();
    Mod rcvModality();
    int rcvFrequency();
    void checkMessage();
};
#endif
