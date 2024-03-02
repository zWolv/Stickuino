#include "Button.h"

Button::Button(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
}

void Button::Update() 
{
    int analogReading = analogRead(pin);
    int reading = (analogReading > 512) ? HIGH : LOW;
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
            }
            else 
            {
                pressed = false;
                if(wasPressed)  // If the button was pressed in the last update
                {
                    
                    pressedFor = millis() - pressedAt;
                    if(callback != nullptr && pressedFor < 500) 
                    {
                    callback();
                    }
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
    this->callback = callback;
}

unsigned long Button::GetPressedAt() const
{
    return pressedAt;
}
