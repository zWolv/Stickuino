#ifndef GLOBALS_H
#define GLOBALS_H

#include <LiquidCrystal.h>

static int redLED = 8;
static int greenLED = 7;
static int yellowLED = 6;
static int tempPin = 9;
static int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
static LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);

#endif