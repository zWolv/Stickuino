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

Timer temperatureTimer(TimerType::REPEAT);

Timer sprayTimer(TimerType::ONCE);

Timer sprayFinishedTimer(TimerType::ONCE);

StateMachine sm(&(Idle)Idle());

Button manualOverrideButton(manualOverridePin);

volatile int overrideSprayDelay = 0;

volatile int nr2SprayDelay = 0;

volatile int nr1SprayDelay = 0;

InMenu inMenu;

void setup() {
  Serial.begin(9600);  // takes up a LOT of memory. -> use lcd for debugging
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  //t.Start(Turnon, 5000);
  sensor.begin();
  temperatureTimer.Start(temperature, 2500);
  manualOverrideButton.SetCallback(ManualOverride);
}


void loop() {
  if(sm.GetState() == &inMenu) {
    sprayTimer.Stop();
    sprayFinishedTimer.Stop();

  }
    sprayTimer.Update();
    sprayFinishedTimer.Update();
    manualOverrideButton.Update();
  // Should temperature still be updated if we are in the menu?
  temperatureTimer.Update();
  sm.Update();
}

void temperature() {
  lcd.clear();
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  lcd.setCursor(0, 0);
  lcd.print((String)temp + " C");
}

void ManualOverride() {
  StartSpray([](){}, overrideSprayDelay);
}
// Following 3 functions should by in 'Triggered'
void Nr1() {
  StartSpray([](){}, nr1SprayDelay);
}

void Nr2() {
  StartSpray([](){StartSpray([](){}, 0);}, nr2SprayDelay); // don't wait with the second spray, only for the first one.
}

// what to do when spray is done, and how long to wait before spraying
void StartSpray(void (*function)(), int time) {
  /*
  sm.SetState(&(Triggered)Triggered());
  sprayTimer.Start(Spray, time); // Call spray after configurable delay
  sprayFinishedTimer.Start([&]() {
    sm.SetState(&(Idle)Idle());
    (*function)();
  }, time + 15000); // Spray happens after 15 seconds + configurable delay
  */
}

void Spray () {
  // spray!!!
}

void MenuOpenInterrupt() {
  sm.NextState(&(InMenu)InMenu());
}

