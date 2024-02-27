#include "States.h"

// Idle state
// green led on
Idle::Idle() 
{
    stateLED[0] = redLED;
}

// In use - type of use unknown
// green + yellow led on
UnknownUse::UnknownUse() 
{
    stateLED[0] = greenLED;
    stateLED[1] = yellowLED;
}

// In use - number 1 use
// green + red led on
Use1::Use1()
{
    stateLED[0] = greenLED;
    stateLED[1] = redLED;
}

// In use - number 2 use
// red led on
Use2::Use2()
{
    stateLED[0] = redLED;
}

// In use - cleaning
// yellow led on
Cleaning::Cleaning()
{
    stateLED[0] = yellowLED;
}

// triggered - spray-shot imminent
// all leds on
Triggered::Triggered()
{
    stateLED[0] = greenLED;
    stateLED[1] = redLED;
    stateLED[2] = yellowLED;
}

// operator menu active
// red + yellow led on
InMenu::InMenu()
{
    stateLED[0] = redLED;
    stateLED[1] = yellowLED;
}