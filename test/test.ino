#include <Timer.h>
#include <LiquidCrystal.h>
#include <StateMachine.h>
#include <PinChangeInterrupt.h>
#include "States.h"
#include "Globals.h"
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Button.h>

OneWire oneWire(tempPin);
DallasTemperature sensor(&oneWire);

Timer sprayFinishedTimer(TimerType::ONCE);

StateMachine sm(Triggered::GetInstance());

Button manualOverrideButton(manualOverridePin);

Timer temperatureTimer(TimerType::REPEAT);
LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);
Button menuButtonLeft(menuButtonLeftPin);
Button menuButtonRight(menuButtonRightPin);


const int manualOverridePin = A1;
const int ldr = A0;
const int menuButtonLeftPin = A2;
const int menuButtonRightPin = A3;
const int redLED = 8;
const int greenLED = 7;
const int yellowLED = 6;
const int tempPin = 9;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int sprayCount = 2400;
float sprayDelay = 0;

void setup() {
  Serial.begin(9600);  // takes up a LOT of memory. -> use lcd for debugging
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(tempPin, INPUT);
  pinMode(ldr, INPUT);
  sensor.begin();
  lcd.begin(16,2);
  temperatureTimer.Start(temperature, 2500);
  attachPCINT(digitalPinToPCINT(manualOverridePin), ManualOverrideISP, RISING);
  attachPCINT(digitalPinToPCINT(menuButtonLeftPin), MenuOpenISP, RISING);
  attachPCINT(digitalPinToPCINT(menuButtonRightPin), MenuOpenISP, RISING);
}


void loop() {
  // Should temperature still be updated if we are in the menu?
  temperatureTimer.Update();
  sm.Update();
  //int read = analogRead(menuButtonLeftPin);
  //Serial.println(read);
}

// Function to update the temperature on the LCD using a timer
void temperature() {
  lcd.clear();
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  lcd.setCursor(0, 0);
  lcd.print((String)temp + " C");
}

// Function for the manual override interrupt
void ManualOverrideISP() {
  // Does this also work when in menu?
  lcd.clear();
  if (&sm.GetState() != InMenu::GetInstance())
    sm.SetState(Triggered::GetInstance());
}

// Following 3 functions should by in 'Triggered'
void Nr1() {
  StartSpray([]() {}, sprayDelay);
}

void Nr2() {
  StartSpray([]() {
    StartSpray([]() {}, 0);
  },
             sprayDelay);  // don't wait with the second spray, only for the first one.
}

// what to do when spray is done, and how long to wait before spraying
void StartSpray(void (*function)(), int time) {
  /* broken
  sm.SetState(&(Triggered)Triggered());
  sprayTimer.Start(Spray, time); // Call spray after configurable delay
  sprayFinishedTimer.Start([&]() {
    sm.SetState(&(Idle)Idle());
    (*function)();
  }, time + 15000); // Spray happens after 15 seconds + configurable delay
  */
}

void Spray() {
  // spray!!!
}

void MenuOpenISP() {
  if (&sm.GetState() != InMenu::GetInstance())
    sm.NextState(InMenu::GetInstance());
}
