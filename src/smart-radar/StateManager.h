#ifndef __STATE_MANAGER__
#define __STATE_MANAGER__

enum Mod { AUTO, SINGLE, MANUAL };

class StateManager {
  private:

    bool alarm;
    bool blinking;
    bool changing;
    Mod modality;

  public:
    StateManager();

    void setAlarm(bool alarm); 
    bool isOnAlarm();
    void setBlinking(bool blinking);
    bool hasToBlink();
    Mod getModality();
    void setModality(Mod modality);
    void setModeChanging(bool resetting);
    bool isModeChanging();
};

#endif
