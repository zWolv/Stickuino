#include "StateMachine.h"

State::State() {
    for(int i = 0; i < 3; i++) {
        stateLED[i] = -1;
    }
}

void State::Enter() 
{
    for(int i : stateLED) {
        if(i != -1) {
            digitalWrite(i, HIGH);
        }
    }
}

void State::Exit() 
{
    for(int i : stateLED) {
        if(i != -1) {
            digitalWrite(i, LOW);
        }
    }
}

void State::Update() 
{
    return;
}

StateMachine::StateMachine(State* state) 
{
    this->state = state;
    state->Enter();
}

void StateMachine::SetState(State* state) 
{
    (this->state)->Exit();
    (this->state) = state;
    (this->state)->Enter();
}

State* StateMachine::GetState() const 
{
    return state;
}

void StateMachine::Update() 
{
        state->Update();
        SetState(nextState);
}

void StateMachine::NextState(State* state) 
{
    nextState = state;
}