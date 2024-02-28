#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include <StateMachine.h>
#include <Timer.h>
#include "Globals.h"
#include <Button.h>

class Idle : public State {
  public:
    Idle();
    void Update() override;
};

class UnknownUse : public State {
  public:
    UnknownUse();
    void Update() override;
};

class Use1 : public State {
  public:
    Use1();
    void Update() override;
};

class Use2 : public State {
  public:
    Use2();
    void Update() override;
};

class Cleaning : public State {
  public:
    Cleaning();
    void Update() override;
};

class Triggered : public State {
  public:
    Triggered();
    void Enter() override;
    void Update() override;
  private:
  Timer timer;
  int delay;
  int count;
};

class InMenu : public State {
  public:
    InMenu();
    void Update() override;
  private:
    Button button1;
    Button button2;
};

#endif