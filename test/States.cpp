#include "States.h"

// Idle state
// RED BLINK AND GREEN BLINK
Idle::Idle() {
  name = "Idle";
}

void Idle::Enter() {
  State::Enter();
  motionState = LOW;
  previousMotionState = LOW;
}

State& Idle::Update() {
  // Detect any use case and go to appropriate state
  Blink(redLED, redTime, redState);
  Blink(greenLED, greenTime, greenState);
  previousMotionState = motionState;
  motionState = digitalRead(motionPin);
  if (motionState == HIGH && previousMotionState == LOW) {
    return *UnknownUse::GetInstance();
  }
  return *this;
}

void Idle::Exit() {
  State::Exit();
  delete Idle::instance;
  Idle::instance = nullptr;
}

Idle* Idle::instance = nullptr;

Idle* Idle::GetInstance() {
  if (Idle::instance == nullptr) {
    Idle::instance = new Idle();
  }
  return Idle::instance;
}

// In use - type of use unknown
// GREEN BLINK
UnknownUse::UnknownUse() {
  name = "Unknown";
}

void UnknownUse::Enter() {
  State::Enter();
  pingSpeed = 50;
  pingTimer = millis();
  cleaning = false;
  previousDoorState = LOW;
  doorState = LOW;
  doorTime = 0;
  door = false;
}

UnknownUse* UnknownUse::instance = nullptr;

UnknownUse* UnknownUse::GetInstance() {
  if (UnknownUse::instance == nullptr) {
    UnknownUse::instance = new UnknownUse();
  }
  return UnknownUse::instance;
}

State& UnknownUse::Update() {
  Blink(greenLED, greenTime, greenState);
  // Need to do some stuff to make usable for this purpose
  bool doorOpen = false;
  if(millis() >= pingTimer) {
    pingTimer += pingSpeed;
    sonar.ping_timer(EchoCheck);
  }
  previousDoorState = doorState;
  doorState = analogRead(magnetPin) > 512 ? HIGH : LOW;
  if(doorState == HIGH && previousDoorState == LOW) { // Door is open
    doorTime = millis();
    door = true;
  }
  else if(doorState == LOW && previousDoorState == HIGH) { // Door is closed
    door = false;
  }

  // Light turns off -> no use
  int light = analogRead(ldr);
  if (light < lightThreshold) {
    return *Idle::GetInstance();
  }

  if(millis() - doorTime > 10000 && door) { // Door has been open for 10 seconds
    return *Cleaning::GetInstance();
  }
  // Measure distances in the toilet from distance sensor to button.
  if(distance > 19 && distance <= 31 && !doorOpen) {
    return *Use2::GetInstance();
  } else if(distance > 31 && distance < 38 && !doorOpen) {
    return *Use1::GetInstance();
  }

  return *this;
}

// Function to check the distance from the distance sensor to the button
static void UnknownUse::EchoCheck() {
  if(sonar.check_timer()) {
    UnknownUse::GetInstance()->distance = sonar.ping_result / US_ROUNDTRIP_CM;
  }
}

void UnknownUse::Exit() {
  State::Exit();
  delete UnknownUse::instance;
  UnknownUse::instance = nullptr;
}

// In use - number 1 use
// GREEN LED
Use1::Use1() {
  name = "Use 1";
  stateLED[0] = greenLED;
}

Use1* Use1::instance = nullptr;

Use1* Use1::GetInstance() {
  if (Use1::instance == nullptr) {
    Use1::instance = new Use1();
  }
  return Use1::instance;
}

State& Use1::Update() {
  // Use case 1 ended
  int read = analogRead(ldr);
  if (read < lightThreshold) {
    return *FinishedUse(1); // 1 spray
  }
  return *this;
}

void Use1::Exit() {
  State::Exit();
  delete Use1::instance;
  Use1::instance = nullptr;
}

// In use - number 2 use
// RED
Use2::Use2() {
  name = "Use 2";
  stateLED[0] = redLED;
}

Use2* Use2::instance = nullptr;

Use2* Use2::GetInstance() {
  if (Use2::instance == nullptr) {
    Use2::instance = new Use2();
  }
  return Use2::instance;
}

State& Use2::Update() {
  // Use case 2 ended
  int read = analogRead(ldr);
  if (read < lightThreshold) { // tweak this value
    return *FinishedUse(2); // 2 spray
  }
  return *this;
}

void Use2::Exit() {
  State::Exit();
  delete Use2::instance;
  Use2::instance = nullptr;
}

// In use - cleaning
// GREEN BLINK AND RED
Cleaning::Cleaning() {
  name = "Cleaning";
  stateLED[0] = redLED;
}

Cleaning* Cleaning::instance = nullptr;

Cleaning* Cleaning::GetInstance() {
  if (Cleaning::instance == nullptr) {
    Cleaning::instance = new Cleaning();
  }
  return Cleaning::instance;
}

State& Cleaning::Update() {
  Blink(greenLED, greenTime, greenState);
  // Cleaning ended
  int read = analogRead(ldr);
  if (read < lightThreshold) {
    return *Idle::GetInstance();
  }
  return *this;
}

void Cleaning::Exit() {
  State::Exit();
  delete Cleaning::instance;
  Cleaning::instance = nullptr;
}

// triggered - spray-shot imminent
// RED BLINK
Triggered::Triggered() {
  name = "Triggered";
}

Triggered* Triggered::instance = nullptr;

Triggered* Triggered::GetInstance() {
  if (Triggered::instance == nullptr) {
    Triggered::instance = new Triggered();
  }
  return Triggered::instance;
}

void Triggered::Enter() {
  State::Enter();
  sprayTimer.Start(Spray, sprayDelay * 1000);  // use recursive function to call 'count' times - delay is in ms
}

void Triggered::Exit() {
  State::Exit();
  sprayTimer.Stop();
  delete Triggered::instance;
  Triggered::instance = nullptr;
}

State& Triggered::Update() {
  Blink(redLED, redTime, redState);
  sprayTimer.Update();
  if(count <= 0) {
    return *Idle::GetInstance();
  }
  return *this;
}

// operator menu active
// GREEN AND RED BLINK
InMenu::InMenu() {
  name = "InMenu";
  stateLED[0] = greenLED;
  state = nullptr;
}

InMenu* InMenu::instance = nullptr;

InMenu* InMenu::GetInstance() {
  if (InMenu::instance == nullptr) {
    InMenu::instance = new InMenu();
  }
  return InMenu::instance;
}

void InMenu::Enter() {
  State::Enter();
  DetachISR();
  temperatureTimer.Stop();
  setting = 0;
  previousSetting = -1;
  menuButtonLeft.SetCallback(LeftButton);
  menuButtonRight.SetCallback(RightButton);
  state = this;
}

State& InMenu::Update() {
  // Menu action
  Blink(redLED, redTime, redState);
  menuButtonLeft.Update();
  menuButtonRight.Update();
  switch (setting) {
    case 0:
      if (previousSetting != setting) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sprays left:" + (String)sprayCount);
        lcd.setCursor(0, 1);
        lcd.print("Next");
        lcd.setCursor(5, 1);
        lcd.print("Reset");
        previousSetting = setting;
      }
      break;
    case 1:
      if (previousSetting != setting) {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Quit");
        lcd.setCursor(10, 1);
        lcd.print("Select");
        previousSetting = setting;
      }
      lcd.setCursor(0, 0);
      lcd.print("Spray delay:" + (String)sprayDelay + "s");
      break;
    case -1:
      if (previousSetting != setting) {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("-");
        lcd.setCursor(7, 1);
        lcd.print("Back");
        lcd.setCursor(15, 1);
        lcd.print("+");
        previousSetting = setting;
      }
      lcd.setCursor(0, 0);
      lcd.print("Spray delay:" + (String)sprayDelay);
      // Hold both buttons for 2 seconds to go back to selection.
      if (menuButtonLeft.PressedFor() > 2000 && menuButtonRight.PressedFor() > 2000 
      && menuButtonLeft.IsClicked() && menuButtonRight.IsClicked()) {
        setting = 1;
        if (temp != sprayDelay) {
          EEPROM.put(sprayDelayIndex, sprayDelay);
        }
      }
      break;
    default:
      break;
  }
  return *state;
}

void InMenu::Exit() {
  State::Exit();
  AttachISR();
  temperatureTimer.Start(LCD, tempTime);
  LCD();
  state = this;
  menuButtonLeft.SetCallback(nullptr);
  menuButtonRight.SetCallback(nullptr);
}

void InMenu::LeftButton() {
  // Left button action
  switch (InMenu::GetInstance()->setting) {
    case 0:
      InMenu::GetInstance()->setting = 1;
      break;
    case 1:
      InMenu::GetInstance()->state = Idle::GetInstance();
      break;
    case -1:
      sprayDelay = max(0, sprayDelay - 0.5f);
    default:
      break;
  }
}

void InMenu::RightButton() {
  // Right button action

  switch (InMenu::GetInstance()->setting) {
    case 0:
      sprayCount = maxSprayCount;
      EEPROM.update(sprayCountIndex, sprayCount);
      break;
    case 1:
      InMenu::GetInstance()->setting = -1;
      InMenu::GetInstance()->temp = sprayDelay;
      break;
    case -1:
      sprayDelay = min(INT8_MAX, sprayDelay + 0.5f);
    default:
      break;
  }
}
