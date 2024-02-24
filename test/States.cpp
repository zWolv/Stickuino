#include "States.h"


// Idle state
// green led on
Idle::Idle()
= default;

// In use - type of use unknown
// green + blue led on
UnknownUse::UnknownUse() 
= default;

// In use - number 1 use
// green + red led on
Use1::Use1()
= default;

// In use - number 2 use
// red led on
Use2::Use2()
= default;

// In use - cleaning
// blue led on
Cleaning::Cleaning()
= default;

// triggered - spray-shot imminent
// all leds on
Triggered::Triggered()
= default;

// operator menu active
// red + blue led on
InMenu::InMenu()
= default;