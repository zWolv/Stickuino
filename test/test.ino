#include <Timer.h>
#include <LiquidCrystal.h>
#include <StateMachine.h>
#include <PinChangeInterrupt.h>
#include "States.h"
#include "Globals.h"
#include <DallasTemperature.h>
#include <OneWire.h>

OneWire oneWire(tempPin);
DallasTemperature sensor(&oneWire);

Timer t(TimerType::REPEAT);

StateMachine sm((Idle) Idle());

void setup() {
  Serial.begin(9600);  // takes up a LOT of memory. -> use lcd for debugging
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  //t.Start(turnon, 5000);
  sensor.begin();
}

void loop() {
  //lcd.clear();
  //lcd.setCursor(0,0);
  //sensor.requestTemperatures();
  //float temp = sensor.getTempC(0);
  //Serial.println(String(temp));
  //delay(1000);
  //lcd.print(String(sensor.getTempCByIndex(0)));
  //t.Update();
}

/*
// Used to test the TimerType::REPEAT
void increment() 
{
  p++;
  lcd.clear();
  lcd.print(String(p));
}

//Used to test the TimerType::ONCE and lcd printing for debugging
void turnon() 
{
  lcd.clear();
  lcd.print(F("turned on"));
  //Serial.print("turned on");
  digitalWrite(13, HIGH);
  delay(2000);
  digitalWrite(13, LOW);
  lcd.clear();
  lcd.print(F("turned off"));
  //t.Start(&turnoff, 5000);
}

void turnoff() 
{
  lcd.clear();
  lcd.print("turned off");
  //Serial.print("turned off");
  digitalWrite(13, LOW);
  t.Start(&turnon, 5000);
}*/

void temperature() {
}
