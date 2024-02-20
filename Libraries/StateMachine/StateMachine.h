#ifndef STATEMACHINE_H
#define STATEMACHINE_H

enum Event {
    START,
    END_USE,
    UNKNOWN_USE_DETECTED,
    NR1_USE_DETECTED,
    NR2_USE_DETECTED,
    CLEANING_DETECTED,
    TRIGGERED,
    MENU_BUTTON_PRESSED
};

class State 
{
public:
    virtual void enter(Event event) = 0;
    virtual void update(Event event) = 0;
    virtual void exit() = 0;
};

class StateMachine 
{
public:
    StateMachine(State* state);

    void setState(State* state);
    State* getState() const;

    void processEvent(Event event);

private:
    State* state;
};



#endif