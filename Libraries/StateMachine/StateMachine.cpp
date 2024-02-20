#include "StateMachine.h"

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

void StateMachine::processEvent(Event event) 
{
    state->update(event);
}