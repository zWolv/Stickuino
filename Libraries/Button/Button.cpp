#include "Button.h"

Button::Button(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
}

void Button::Update() 
{
    int reading = digitalRead(pin);
    bool wasPressed = pressed;
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
                if(!pressed) 
                {
                    pressedAt = millis();
                }
                pressed = true;
                if(callback != nullptr) 
                {
                    callback();
                }
            }
            else 
            {
                pressed = false;
                pressedFor = millis() - pressedAt;
                if(wasPressed)  // If the button was pressed in the last update
                {
                    clicked = true;
                    clickedAt = millis();  // Record the time when the button was clicked
                }
            }
        }
    }
    else if(millis() - clickedAt > clickHoldTime)  // If the hold time has passed
    {
        clicked = false;
    }
}

bool Button::IsClicked() const
{
    return clicked;
}

unsigned long Button::PressedFor() const
{
    return pressedFor;
}

void Button::SetCallback(void (*callback)())
{
    this->callback = callback;
}
