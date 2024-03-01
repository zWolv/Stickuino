#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>

// States will be singletons
class State 
{
public:
    State();
    State(const State&) = delete;
    State& operator=(const State&) = delete; 
    virtual void Enter();
    virtual void Exit();
    virtual State& Update();
    String name;
protected:
    int stateLED[3];
};

class StateMachine 
{
public:
    StateMachine(State* state);

    void SetState(volatile State* state);
    State& GetState() const;
    void NextState(State* state);
    void Update();
private:
    State* state;
    volatile State* nextState;
};



#endif