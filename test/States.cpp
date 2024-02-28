#include "States.h"

// Idle state
// green led on
Idle::Idle() 
{
    stateLED[0] = redLED;
}


void Idle::Update() {
    // Detect any use case and go to appropriate state
    /*
    if (usage detected) {
        sm.SetState((UnknownUse)UnknownUse());
    }
    */
}

// In use - type of use unknown
// green + yellow led on
UnknownUse::UnknownUse() 
{
    stateLED[0] = greenLED;
    stateLED[1] = yellowLED;
}

void UnknownUse::Update() {
    // Use case detected
    /*
    if (use case 1 detected) {
        sm.SetState((Use1)Use1());
    }
    else if (use case 2 detected) {
        sm.SetState((Use2)Use2());
    }
    else if (cleaning detected) {
        sm.SetState((Cleaning)Cleaning());
    }
    */
}

// In use - number 1 use
// green + red led on
Use1::Use1()
{
    stateLED[0] = greenLED;
    stateLED[1] = redLED;
}

void Use1::Update() {
    // Use case 1 ended
    /*
    if (use case ended) {
        sm.SetState((Triggered)Triggered(usecase1 delay, 1 time));
    }
    */
}

// In use - number 2 use
// red led on
Use2::Use2()
{
    stateLED[0] = redLED;
}

void Use2::Update() {
    // Use case 2 ended
    /*
    if (use case ended) {
        sm.SetState((Triggered)Triggered(usecase2 delay, 2 times));
    }
    */
}

// In use - cleaning
// yellow led on
Cleaning::Cleaning()
{
    stateLED[0] = yellowLED;
}

void Cleaning::Update() {
    // Cleaning ended
    /*
    if (cleaning ended) {
        sm.SetState((Idle)Idle());
    }
    */
}

// triggered - spray-shot imminent
// all leds on
Triggered::Triggered() : timer(TimerType::ONCE)
{
    stateLED[0] = greenLED;
    stateLED[1] = redLED;
    stateLED[2] = yellowLED;
}

void Triggered::Enter() {
    // Start spray timer
    /*
    sprayTimer.Start(Spray, delay); // use recursive lambda to call 'count' times
    */
}

void Triggered::Update() {
    // Spray shot
    /*
    if (spray shot) {
        sm.SetState((Idle)Idle());
    }
    */
}

// operator menu active
// red + yellow led on
InMenu::InMenu() : button1(menuButton1Pin), button2(menuButton2Pin)
{
    stateLED[0] = redLED;
    stateLED[1] = yellowLED;
}

void InMenu::Update() {
    // Menu action
    /*
    define a bunch of menu actions.
    */
}