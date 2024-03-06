#include <Timer.h>
#include <LiquidCrystal.h>
#include <StateMachine.h>
#include "States.h"
#include "Globals.h"
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Button.h>
#include <EEPROM.h>
#include <NewPing.h>

OneWire oneWire(tempPin);
DallasTemperature sensor(&oneWire);

Timer sprayFinishedTimer(TimerType::ONCE);

StateMachine sm(Idle::GetInstance());

Button manualOverrideButton(manualOverridePin, PinType::ANALOG);

Timer temperatureTimer(TimerType::REPEAT);
LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);
Button menuButtonLeft(menuButtonLeftPin);
Button menuButtonRight(menuButtonRightPin);


const int manualOverridePin = A1;
const int ldr = A0;
const int menuButtonLeftPin = 2;
const int menuButtonRightPin = 3;
const int redLED = 8;
const int greenLED = 7;
const int yellowLED = 6;
const int tempPin = 9;  // can go on analog too
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 13, d7 = 10;
float sprayCount = 2400;
float sprayDelay = 0;
const int maxSprayCount = 2400;
const int distTrig = A4;
const int distEcho = A5;
const int motionPin = A2;
const int magnetPin = A3;
const int sprayWaitTime = 25000;
const int sprayPin = A6;

int sprayCountIndex = 0;
int sprayDelayIndex = 4;

NewPing sonar(distTrig, distEcho, 50);

void setup() {
  float read;
  read = EEPROM.get(sprayCountIndex, read);
  if (isnan(read)) {
    EEPROM.put(sprayCountIndex, sprayCount);
  } else {
    sprayCount = read;
  }
  read = EEPROM.get(sprayDelayIndex, read);
  if (isnan(read)) {
    EEPROM.put(sprayDelayIndex, sprayDelay);
  } else {
    sprayDelay = read;
  }
  Serial.begin(9600);  // takes up a LOT of memory. -> use lcd for debugging
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(tempPin, INPUT);
  pinMode(ldr, INPUT);
  pinMode(magnetPin, INPUT_PULLUP);
  sensor.begin();
  lcd.begin(16, 2);
  temperatureTimer.Start(Temperature, 2500);
  Temperature();
  AttachISR();
  manualOverrideButton.SetCallback(ManualOverrideSR);
}

int pinState = LOW;
int pinStateP = LOW;

void loop() {
  // Should temperature still be updated if we are in the menu?
  temperatureTimer.Update();
  sm.Update();
  if (&sm.GetState() != InMenu::GetInstance()) {
    manualOverrideButton.Update();
  }
  /*
  pinStateP = pinState;
  pinState = analogRead(motionPin) > 512 ? HIGH : LOW;
  if (pinStateP == LOW && pinState == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    // TODO: turn on alarm, light or activate a device ... here
  }
  else
  if (pinStateP == HIGH && pinState == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
    // TODO: turn off alarm, light or deactivate a device ... here
  }*/
}

// Function to update the temperature on the LCD using a timer
void Temperature() {
  lcd.clear();
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  lcd.setCursor(0, 0);
  lcd.print((String)temp + " C");
}

State& FinishedUse(int sprayCount) {
  int read = analogRead(ldr);
  if (read < 512) {
    Triggered& state = *Triggered::GetInstance();
    state.count = sprayCount;
    return state;
  }
}

// Function for the manual override interrupt
void ManualOverrideSR() {
  // Does this also work when in menu?
  if (&sm.GetState() != InMenu::GetInstance() && &sm.GetState() != Triggered::GetInstance())
    sm.NextState(Triggered::GetInstance());
    Triggered::GetInstance()->count = 1;
}

void AttachISR() {
  attachInterrupt(digitalPinToInterrupt(menuButtonLeftPin), MenuOpenISP, FALLING);
  attachInterrupt(digitalPinToInterrupt(menuButtonRightPin), MenuOpenISP, FALLING);
}

void DetachISR() {
  detachInterrupt(digitalPinToInterrupt(menuButtonLeftPin));
  detachInterrupt(digitalPinToInterrupt(menuButtonRightPin));
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
