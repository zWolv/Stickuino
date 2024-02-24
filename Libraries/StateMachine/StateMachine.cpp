#include "StateMachine.h"

State::State() {
    for(int i = 0; i < 3; i++) {
        stateLED[i] = -1;
    }
}

void State::enter(Event event) 
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

StateMachine::StateMachine(State* state) 
{
    this->state = state;
    state->enter(Event::START);
}

void StateMachine::setState(State* state) 
{
    (this->state)->exit();
    (this->state) = state;
    (this->state)->enter(Event::START);
}

State* StateMachine::getState() const 
{
    return state;
}

/*
void StateMachine::processEvent(Event event) 
{
    state->update(event);
}
*/