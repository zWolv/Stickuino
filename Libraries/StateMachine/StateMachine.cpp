#include "StateMachine.h"

State::State() {
    for(int i = 0; i < 3; i++) {
        stateLED[i] = -1;
    }
}

void State::enter() 
{
    for(int i : stateLED) {
        if(i != -1) {
            digitalWrite(i, HIGH);
        }
    }
}

void State::exit() 
{
    for(int i : stateLED) {
        if(i != -1) {
            digitalWrite(i, LOW);
        }
    }
}

void State::update() 
{
    return;
}

StateMachine::StateMachine(const State& state) 
{
    this->state = state;
    state.enter();
}

void StateMachine::setState(const State& state) 
{
    (this->state).exit();
    (this->state) = state;
    (this->state).enter();
}

State StateMachine::getState() const 
{
    return state;
}

void StateMachine::update() 
{
    state.update();
}