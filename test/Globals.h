#ifndef GLOBALS_H
#define GLOBALS_H

#include <LiquidCrystal.h>

static const int manualOverridePin = 13;
static const int redLED = 8;
static const int greenLED = 7;
static const int yellowLED = 6;
static const int tempPin = 9;
static const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
static LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);

#endif