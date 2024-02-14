#include "Timer.h"

Timer::Timer(TimerType type) 
{
    this->type = type;
    callback = nullptr;
    start = 0;
    interval = 0;
}

void Timer::Start(void (*func)(), int milliseconds) 
{
    if(running) return; // Prevent from running multiple times
    callback = func;
    start = millis();
    interval = milliseconds;
    running = true;
}

void Timer::Update() {
    if(!running) return; // No need to update if it's not running
    
    if(millis() - start >= interval) 
    {
        running = false;
        ((void (*)())callback)();
        if(type == TimerType::REPEAT) 
        {
            running = true;
            start = millis();
        }
    } 
}
