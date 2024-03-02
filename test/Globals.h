#ifndef GLOBALS_H
#define GLOBALS_H

#include <LiquidCrystal.h>
#include <Button.h>
#include "States.h"
#include <Timer.h>

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
extern int sprayCount;
extern float sprayDelay;
extern Button menuButtonLeft;
extern Button menuButtonRight;
extern Timer temperatureTimer;
extern LiquidCrystal lcd;

// Forward declarations
void MenuOpenISP();
void temperature();
void attachISR();
void detachISR();

#endif