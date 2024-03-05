#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include <StateMachine.h>
#include <Timer.h>
#include "Globals.h"
#include <Button.h>
#include <EEPROM.h>
#include <NewPing.h>

class Idle : public State {
public:
  static Idle* GetInstance();
  State& Update() override;
  void Exit() override;
private:
  static Idle* instance;
  Idle();
};

class UnknownUse : public State {
public:
  static UnknownUse* GetInstance();
  void Exit() override;
  void Enter() override;
  State& Update() override;
private:
  static UnknownUse* instance;
  UnknownUse();
  static void EchoCheck();
  unsigned int pingSpeed;
  unsigned long pingTimer;
  int distance;
  int doorTime;
  int doorState;
  int previousDoorState;
  bool cleaning;
};

class Use1 : public State {
public:
  static Use1* GetInstance();
  void Exit() override;
  State& Update() override;
private:
  static Use1* instance;
  Use1();
};

class Use2 : public State {
public:
  static Use2* GetInstance();
  State& Update() override;
  void Exit() override;
private:
  static Use2* instance;
  Use2();
};

class Cleaning : public State {
public:
  static Cleaning* GetInstance();
  State& Update() override;
  void Exit() override;
private:
  static Cleaning* instance;
  Cleaning();
};

class Triggered : public State {
public:
  static Triggered* GetInstance();
  void Enter() override;
  State& Update() override;
  void Exit() override;
  void TimerFunction();
  static void StaticTimerFunction();
private:
  static Triggered* instance;
  Triggered();
  void Spray();
  Timer timer;
  int count;
};

class InMenu : public State {
public:
  static InMenu* GetInstance();
  State& Update() override;
  void Enter() override;
  void Exit() override;
private:
  static void LeftButton();
  static void RightButton();
  static InMenu* instance;
  int setting;
  InMenu();
  int previousSetting;
  float temp;
  State* state;
};

#endif