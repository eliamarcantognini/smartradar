#include "config.h"
#include "RadarImpl.h"
#include "MsgService.h"
#include "Scheduler.h"
#include "StateManager.h"
#include "BlinkingTask.h"
#include "AutoModeTask.h"
#include "SingleModeTask.h"
#include "ManualModeTask.h"
#include "ChangingModeTask.h"
#include "Led.h"
#include "Pir.h"

Scheduler sched;

void setup(){  
  sched.init(100);

  MsgService.init();

  StateManager* sManager = new StateManager();
  UserConsole* console = new UserConsole();
  Radar* radar = new RadarImpl(SERVO_PIN, SONAR_ECHO_PIN, SONAR_TRIG_PIN, POT_PIN);
  
  Task* t1 = new BlinkingTask(L1_PIN,L2_PIN, sManager, console);
  t1->init(100);
  t1->enable();
  
  Task* t2 = new AutoModeTask(radar, sManager, console);
  t2->init(100);
  
  Task* t3 = new SingleModeTask(new Pir(PIR_PIN), radar, sManager, console);
  t3->init(100);

  Task* t4 = new ManualModeTask(radar, sManager, console);
  t4->init(100);
  t4->enable();
  
  Task* t0 = new ChangingModeTask(B1_PIN, B2_PIN, B3_PIN, sManager, console, t2, t3, t4);
  t0->init(100);
  t0->enable();
  
  sched.addTask(t0);
  sched.addTask(t1);
  sched.addTask(t2);
  sched.addTask(t3);
  sched.addTask(t4);

  console->displayReady();
}

void loop(){
  sched.run();
}
