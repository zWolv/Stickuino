#ifndef GLOBALS_H
#define GLOBALS_H

#include <LiquidCrystal.h>
#include <Button.h>
#include <Timer.h>
#include <NewPing.h>
#include <StateMachine.h>



// Global variables
extern const int manualOverridePin;
extern const int ldr;
extern const int menuButtonLeftPin;
extern const int menuButtonRightPin;
extern const int redLED;
extern unsigned long redTime;
extern int redState;
extern const int greenLED;
extern unsigned long greenTime;
extern int greenState;
extern const int tempPin;
extern const int rs, en, d4, d5, d6, d7;
extern const int maxSprayCount;
extern float sprayCount;
extern int sprayCountIndex;
extern float sprayDelay;
extern int sprayDelayIndex;
extern Button menuButtonLeft;
extern Button menuButtonRight;
extern Timer temperatureTimer;
extern LiquidCrystal lcd;
extern const int distTrig;
extern const int distEcho;
extern const int motionPin;
extern const int magnetPin;
extern NewPing sonar;
extern const int sprayWaitTime;
extern const int sprayPin;
extern const int tempTime;
extern const int lightThreshold;
extern Timer sprayTimer;

// Forward declarations
class Triggered;

void MenuOpenISP();
void LCD();
void AttachISR();
void DetachISR();
void EchoCheck();
Triggered* FinishedUse(int sprayCount);
void Blink(const int& pin, unsigned long& time, int& state);
void Spray();
void SprayFinished();

#endif