#ifndef GLOBALS_H
#define GLOBALS_H

#include <LiquidCrystal.h>
#include <Button.h>
#include "States.h"
#include <Timer.h>
#include <NewPing.h>


// Global variables
extern const int manualOverridePin;
extern const int ldr;
extern const int menuButtonLeftPin;
extern const int menuButtonRightPin;
extern const int redLED;
extern const int greenLED;
extern const int yellowLED;
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

// Forward declarations
void MenuOpenISP();
void temperature();
void attachISR();
void detachISR();
void echoCheck();

#endif