#ifndef GLOBALS_H
#define GLOBALS_H

#include <LiquidCrystal.h>
#include <Button.h>
#include "States.h"

const int manualOverridePin = A1;
const int ldr = A0;
const int menuButtonLeftPin = A2;
const int menuButtonRightPin = A3;
const int redLED = 8;
const int greenLED = 7;
const int yellowLED = 6;
const int tempPin = 9;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
static LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);
static int sprayCount = 2400;
static float sprayDelay = 0;
static Button menuButtonLeft(menuButtonLeftPin);
static Button menuButtonRight(menuButtonRightPin);
static Timer temperatureTimer(TimerType::REPEAT);

// Forward declarations
void ManualOverrideISP();
void MenuOpenISP();
void temperature();

#endif