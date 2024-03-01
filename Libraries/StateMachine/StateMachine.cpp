#include "StateMachine.h"

State::State() {
    name = "Base State";
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

State& State::Update() 
{
    return *this;
}

StateMachine::StateMachine(State* state) 
{
    this->state = state;
    this->state->Enter();
}

void StateMachine::SetState(volatile State* state) 
{
    if(state == nullptr) return;
    (this->state)->Exit();
    (this->state) = state;
    (this->state)->Enter();
}

State& StateMachine::GetState() const 
{
    return *state;
}

void StateMachine::Update() 
{
    State* next = &state->Update();
    if(next != state)
        SetState(next);
    SetState(nextState);
    nextState = nullptr;
}

void StateMachine::NextState(State* state) 
{
    nextState = state;
}