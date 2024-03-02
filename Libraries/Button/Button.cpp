#include "Button.h"

Button::Button(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
}

Button::Button(int pin, PinType pinType)
{
    this->pin = pin;
    pinMode(pin, INPUT);
    this->pinType = pinType;
}

void Button::Update() 
{
    int reading;
    if(pinType == ANALOG) 
    {
        reading = analogRead(pin);
        reading = reading > 512 ? HIGH : LOW;
    }
    else 
    {
        reading = digitalRead(pin);
    }
    wasPressed = pressed;

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
            }
            else 
            {
                pressed = false;
                if(wasPressed)
                {
                    if(pressedAt != 0)
                        pressedFor = millis() - pressedAt;
                    pressedAt = 0;
                    clicked = true;
                    clickedAt = millis();

                    if(callback != nullptr && pressedFor < 500) 
                    {
                        callback();
                    }
                }
            }
        }
    }
    else if(millis() - clickedAt > clickHoldTime)  // If the hold time has passed
    {
        clicked = false;
    }
    previousState = reading;
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
    // make sure the previous state is set to the current state when we want to use the callback.
    previousState = digitalRead(pin);
    debouncedState = previousState;
    this->callback = callback;
}
