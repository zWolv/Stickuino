#include <Timer.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Timer t = {TimerType::REPEAT};


void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);  -- takes up a LOT of memory. -> use lcd for debugging
  pinMode(13, OUTPUT);
  //t.Start(&turnon, 5000);
  lcd.begin(16, 2);
  lcd.print("nothing is");
  lcd.setCursor(0,1);
  lcd.print("happening");
}

void loop() {
  // put your main code here, to run repeatedly:
  //t.Update();
}

/*
// Used to test the TimerType::REPEAT
void increment() {
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

void turnoff() {
  lcd.clear();
  lcd.print("turned off");
  //Serial.print("turned off");
  digitalWrite(13, LOW);
  t.Start(&turnon, 5000);
}*/


