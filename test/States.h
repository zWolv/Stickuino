#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include <StateMachine.h>
#include <Timer.h>
#include "Globals.h"

class Idle : public State {
  public:
    Idle();
};

class UnknownUse : public State {
  public:
    UnknownUse();
};

class Use1 : public State {
  public:
    Use1();
};

class Use2 : public State {
  public:
    Use2();
};

class Cleaning : public State {
  public:
    Cleaning();
};

class Triggered : public State {
  public:
    Triggered();
};

class InMenu : public State {
  public:
    InMenu();
};

#endif