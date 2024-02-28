#ifndef GLOBALS_H
#define GLOBALS_H

#include <LiquidCrystal.h>

const int manualOverridePin = 13;
const int menuButton1Pin = A1;
const int menuButton2Pin = A0;
const int redLED = 8;
const int greenLED = 7;
const int yellowLED = 6;
const int tempPin = 9;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
static LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);

#endif