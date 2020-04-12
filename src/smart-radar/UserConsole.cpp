#include "UserConsole.h"

UserConsole::UserConsole() {
  this->direction = 0;
  this->mode = Mod(-1);
  this->frequency = 0;
};

void UserConsole::reset(char param) {
  switch(param){
    case 'd': this->direction = 0; break;
    case 'm': this->mode = Mod(-1); break;
    case 'f': this->frequency = 0; break;
  }
}

void UserConsole::displayModality(Mod modality) {
  MsgService.sendMsg(String("sr:m|")+modality);
};

void UserConsole::displayServoDirection(int dir) {
  MsgService.sendMsg(String("lo:r|")+dir);
};

void UserConsole::displaySaveMode(bool on){
  MsgService.sendMsg(String("sr:s|")+(on ? 1 : 0));
};

void UserConsole::displayAlarm(bool on){
  MsgService.sendMsg(String("sr:a|")+(on ? 1 : 0));  
};

void UserConsole::displayObjectDistance(float pos) {
  if (pos > 0) {
    MsgService.sendMsg(String("lo:d|")+pos);
  }
};

void UserConsole::displayReady() {
  MsgService.sendMsg("sr:r");
};

int UserConsole::rcvDirection() {
  int tmp = this->direction;
  reset('d');
  return tmp;
};

Mod UserConsole::rcvModality() {
  int tmp = this->mode;
  reset('m');
  return Mod(tmp);
};

int UserConsole::rcvFrequency() {
  int tmp = this->frequency;
  reset('f');
  return tmp;
};

void UserConsole::checkMessage() {
  lastMsg = MsgService.receiveMsg();
  if(lastMsg != NULL){
   String msg = lastMsg->getContent();
   if(msg.startsWith(prefix)){
    String c = msg.substring(prefix.length());
    String sub = c.substring(2);
    switch(c[0]){
      case 'm': mode = Mod(sub.toInt());
      case 'd': direction = sub.toInt();
      case 'f': frequency = sub.toInt();
    }
   }
  }
};
