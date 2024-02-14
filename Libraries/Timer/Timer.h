#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

enum class TimerType { ONCE, REPEAT };

class Timer 
{
public:
    Timer(TimerType type);
    void Start(void (*func)(), int milliseconds); // Start a timer and provide a function that needs to run when it finished
    void Update(); // Call this in the loop to run the timer.
    // ONCE: Run the timer once and stop
    // REPEAT: Run the timer and repeat
private:
    void* callback;
    unsigned long start;
    unsigned long interval;
    bool running;
    TimerType type;
};



#endif