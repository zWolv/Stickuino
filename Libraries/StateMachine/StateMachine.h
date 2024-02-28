#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>

class State 
{
public:
    State();
    
public:
    void Enter();
    void Exit();
    void Update();

protected:
    int stateLED[3];
};

class StateMachine 
{
public:
    StateMachine(const State& state);

    void SetState(const State& state);
    State GetState() const;
    void Update();
private:
    State state;
};



#endif