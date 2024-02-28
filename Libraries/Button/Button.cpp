#include "Button.h"

Button::Button(int pin, void (*function)())
{
    this->pin = pin;
    this->function = function;
    pinMode(pin, INPUT);
}

Button::update() 
{
    int reading = digitalRead(pin);
    if(reading != previousState) 
    {
        previousDebounceTime = millis();
    }
    if(millis() - previousDebounceTime > debounceDelay) 
    {
        if(reading != debouncedState) 
        {
            debouncedState = reading;
            if(debouncedState == LOW) 
            {
                if(function != nullptr)
                    (*function)();
            }
        }
    }
}
