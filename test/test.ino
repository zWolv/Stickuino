// Our own libraries
#include <Timer.h>
#include <StateMachine.h>
#include "States.h"
#include "Globals.h"
#include <Button.h>
// Libraries not owned by us
#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <EEPROM.h>
#include <NewPing.h>

// Local variables
OneWire oneWire(tempPin);
DallasTemperature sensor(&oneWire);
StateMachine sm(Idle::GetInstance());
Button manualOverrideButton(manualOverridePin, PinType::ANALOG);
const int distance = 58;

// Global variables -- These are marked extern in Globals.h
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
const int tempPin = 9;  // can go on analog too
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 13, d7 = 10;
float sprayCount = 2400;
float sprayDelay = 0;
const int maxSprayCount = 2400;
const int distTrig = A4;
const int distEcho = A5;
const int motionPin = A2;
const int magnetPin = A3;
const int sprayWaitTime = 20000;
const int sprayPin = 6;               
unsigned long redTime = 0;
unsigned long greenTime = 0;
int redState = LOW;
int greenState = LOW;
int sprayCountIndex = 0;
int sprayDelayIndex = 4;
NewPing sonar(distTrig, distEcho, distance);
const int tempTime = 1500;
const int lightThreshold = 680;
Timer sprayTimer(TimerType::ONCE);

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
  pinMode(tempPin, INPUT);
  pinMode(ldr, INPUT);
  pinMode(magnetPin, INPUT_PULLUP);
  pinMode(sprayPin, OUTPUT);
  sensor.begin();
  lcd.begin(16, 2);
  temperatureTimer.Start(LCD, tempTime);
  LCD();
  AttachISR();
  manualOverrideButton.SetCallback(ManualOverrideSR);
}

void loop() {
  temperatureTimer.Update();
  sm.Update();
  if (&sm.GetState() != InMenu::GetInstance()) {
    manualOverrideButton.Update();
  }
  
}

// Function to blink an LED
void Blink(int const& pin, unsigned long& time, int& state) {
  if (millis() - time > 500) {
    state = state == HIGH ? LOW : HIGH;
    digitalWrite(pin, state);
    time = millis();
  }
}

// Function to update the temperature on the LCD using a timer
void LCD() {
  lcd.clear();
  sensor.requestTemperatures();
  int temp = sensor.getTempCByIndex(0);
  lcd.setCursor(0, 0);
  lcd.print((String)temp + " C");
  lcd.setCursor(0, 1);
  lcd.print("Sprays: " + (String)sprayCount);
  lcd.setCursor(6, 0);
  lcd.print(sm.GetState().name);
}

// Transition to the triggered state with x amount of sprays
Triggered* FinishedUse(int sprayCount) {
  int read = analogRead(ldr);
  if (read < 512) {
    Triggered* state = Triggered::GetInstance();
    state->count = sprayCount;
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

// Attach and detach the interrupts for the menu buttons
void AttachISR() {
  attachInterrupt(digitalPinToInterrupt(menuButtonLeftPin), MenuOpenISP, FALLING);
  attachInterrupt(digitalPinToInterrupt(menuButtonRightPin), MenuOpenISP, FALLING);
}

void DetachISR() {
  detachInterrupt(digitalPinToInterrupt(menuButtonLeftPin));
  detachInterrupt(digitalPinToInterrupt(menuButtonRightPin));
}

// Interrupt service routine for the menu buttons
void MenuOpenISP() {
  if (&sm.GetState() != InMenu::GetInstance())
    sm.NextState(InMenu::GetInstance());
}


void Spray() {
  // Do the spray
  digitalWrite(sprayPin, HIGH);  
  sprayTimer.Start(SprayFinished, sprayWaitTime); // Call SprayFinished after 25 seconds
}

void SprayFinished() {
  digitalWrite(sprayPin, LOW);
  Triggered::GetInstance()->count--;
  if (Triggered::GetInstance()->count > 0) {
    Spray();
  }
}