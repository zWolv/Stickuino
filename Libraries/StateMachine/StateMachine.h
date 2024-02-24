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

protected:
    int stateLED[3];
};

class StateMachine 
{
public:
    StateMachine(State* state);

    void setState(State* state);
    State* getState() const;

private:
    State* state;
};



#endif