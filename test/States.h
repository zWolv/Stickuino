#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include <StateMachine.h>
#include <Timer.h>
#include "Globals.h"

class Idle : State {
  public:
    Idle();
};

class UnknownUse : State {
  public:
    UnknownUse();
};

class Use1 : State {
  public:
    Use1();
};

class Use2 : State {
  public:
    Use2();
};

class Cleaning : State {
  public:
    Cleaning();
};

class Triggered : State {
  public:
    Triggered();
};

class InMenu : State {
  public:
    InMenu();
};

#endif