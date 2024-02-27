#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>

class State 
{
public:
    State();
    
public:
    void enter();
    void exit();
    void update();

protected:
    int stateLED[3];
};

class StateMachine 
{
public:
    StateMachine(const State& state);

    void setState(const State& state);
    State getState() const;
    void update();
private:
    State state;
};



#endif