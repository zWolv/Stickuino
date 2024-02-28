#include "Button.h"

Button::Button(int pin)
{
    this->pin = pin;
    function = nullptr;
    pinMode(pin, INPUT);
}

void Button::update() 
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

void Button::setCallback(void (*function)()) 
{
    this->function = function;
}
