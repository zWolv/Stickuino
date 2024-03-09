/*
WRITTEN BY THOMAS VAN EGMOND
8471533
*/

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

enum class TimerType { ONCE, REPEAT };
// ONCE: Run the timer once and stop
// REPEAT: Run the timer and repeat

class Timer 
{
public:
    Timer(TimerType type);                                                  // constructor
    void Start(void (*func)(), int milliseconds);                           // Start a timer and provide a function that needs to run when it finished
    void Update();                                                          // Call this in the loop to run the timer.
    void Stop();
private:
    void  (*callback)();                                                    // pointer to callback function
    unsigned long start;                                                    // starting time
    unsigned long interval;                                                 // time interval
    bool running;                                                           // is the timer running
    TimerType type;                                                         // type of timer                                                   
};



#endif