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
