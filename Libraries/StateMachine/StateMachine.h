#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>

class State 
{
public:
    State();
    
public:
    virtual void Enter();
    void Exit();
    virtual void Update();

protected:
    int stateLED[3];
};

class StateMachine 
{
public:
    StateMachine(State* state);

    void SetState(State* state);
    State* GetState() const;
    void NextState(State* state);
    void Update();
private:
    volatile State* state;
    volatile State* nextState;
};



#endif