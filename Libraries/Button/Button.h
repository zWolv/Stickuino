#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <Timer.h>

class Button 
{
public:
    Button(int pin);
    void Update();
    bool IsClicked() const;
    unsigned long PressedFor() const;
private:
    int previousState = HIGH;
    int debouncedState = HIGH;
    unsigned long previousDebounceTime = 0;
    const unsigned long debounceDelay = 50;
    int pin;
    bool pressed = false;
    unsigned long pressedFor = 0;
    unsigned long pressedAt = 0;
    bool clicked = false;
    int clickHoldTime = 250; // Time to keep the button marked as clicked to allow for using 2 buttons at the same time for a single action
};


#endif