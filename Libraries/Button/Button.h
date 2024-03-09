/*
WRITTEN BY THOMAS VAN EGMOND
8471533
*/


#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <Timer.h>

enum PinType { DIGITAL, ANALOG };

class Button 
{
public:
    Button(int pin);
    Button(int pin, PinType pinType); // 0 will be digital, 1 will be analog
    void Update();
    bool IsClicked() const;
    unsigned long PressedFor() const;
    void SetCallback(void (*callback)());
private:
    int previousState = HIGH;
    int debouncedState = HIGH;
    unsigned long previousDebounceTime = 0;
    const unsigned long debounceDelay = 50;
    int pin;
    bool pressed = false;
    bool wasPressed = false;
    unsigned long pressedFor = 0;
    unsigned long pressedAt = 0;
    bool clicked = false;
    unsigned long clickedAt = 0;
    int clickHoldTime = 250; // Time to keep the button marked as clicked to allow for using 2 buttons at the same time for a single action
    void (*callback)(); // Pointer to a function that will be called when the button is clicked if a singular call is needed
    PinType pinType = DIGITAL;
};


#endif