#include "StateManager.h"

StateManager::StateManager() {
  alarm = false;
  blinking = false;
  changing = false;
}

void StateManager::setAlarm(bool alarm) { 
  this->alarm = alarm; 
}

bool StateManager::isOnAlarm() { 
  return alarm; 
}

void StateManager::setBlinking(bool blinking) { 
  this->blinking = blinking; 
}

bool StateManager::hasToBlink() { 
  return blinking; 
}

Mod StateManager::getModality() {
  return modality;
}

void StateManager::setModality(Mod modality) {
  this->modality = modality;
}

void StateManager::setModeChanging(bool changing) {
  this->changing = changing;
}

bool StateManager::isModeChanging() {
  return changing;
}
