#ifndef GLOBALS_H
#define GLOBALS_H

#include<LiquidCrystal.h>
#include <Arduino.h>

extern int redLED;
extern int greenLED;
extern int blueLED;
extern const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
extern LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#endif