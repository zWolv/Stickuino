#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <Timer.h>

class Button 
{
public:
    Button(int pin);
    void Update();
    void SetCallback(void (*function)());
private:
    int previousState = HIGH;
    int debouncedState = HIGH;
    unsigned long previousDebounceTime = 0;
    const unsigned long debounceDelay = 50;
    int pin;
    void (*function)();
};


#endif