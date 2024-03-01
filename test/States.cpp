#include "States.h"

// Idle state
// green led on
Idle::Idle() {
    name = "Idle";
  stateLED[0] = redLED;
}


State& Idle::Update() {
  // Detect any use case and go to appropriate state
  /*
    if (usage detected) {
        sm.SetState((UnknownUse)UnknownUse());
    }
    */
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
// green + yellow led on
UnknownUse::UnknownUse() {
    name = "UnknownUse";
  stateLED[0] = greenLED;
  stateLED[1] = yellowLED;
}

UnknownUse* UnknownUse::instance = nullptr;

UnknownUse* UnknownUse::GetInstance() {
  if (UnknownUse::instance == nullptr) {
    UnknownUse::instance = new UnknownUse();
  }
  return UnknownUse::instance;
}

State& UnknownUse::Update() {
  // Use case detected
  /*
    if (use case 1 detected) {
        sm.SetState((Use1)Use1());
    }
    else if (use case 2 detected) {
        sm.SetState((Use2)Use2());
    }
    else if (cleaning detected) {
        sm.SetState((Cleaning)Cleaning());
    }
    */
  return *this;
}

void UnknownUse::Exit() {
    State::Exit();
  delete UnknownUse::instance;
  UnknownUse::instance = nullptr;
}

// In use - number 1 use
// green + red led on
Use1::Use1() {
    name = "Use1";
  stateLED[0] = greenLED;
  stateLED[1] = redLED;
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
  /*
    if (use case ended) {
        sm.SetState((Triggered)Triggered(once));
    }
    */
  return *this;
}

void Use1::Exit() {
    State::Exit();
  delete Use1::instance;
  Use1::instance = nullptr;
}

// In use - number 2 use
// red led on
Use2::Use2() {
    name = "Use2";
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
  /*
    if (use case ended) {
        sm.SetState((Triggered)Triggered(twice));
    }
    */
  return *this;
}

void Use2::Exit() {
    State::Exit();
  delete Use2::instance;
  Use2::instance = nullptr;
}

// In use - cleaning
// yellow led on
Cleaning::Cleaning() {
    name = "Cleaning";
  stateLED[0] = yellowLED;
}

Cleaning* Cleaning::instance = nullptr;

Cleaning* Cleaning::GetInstance() {
  if (Cleaning::instance == nullptr) {
    Cleaning::instance = new Cleaning();
  }
  return Cleaning::instance;
}

State& Cleaning::Update() {
  // Cleaning ended
  /*
    if (cleaning ended) {
        sm.SetState((Idle)Idle());
    }
    */
  return *this;
}

void Cleaning::Exit() {
    State::Exit();
  delete Cleaning::instance;
  Cleaning::instance = nullptr;
}

// triggered - spray-shot imminent
// all leds on
Triggered::Triggered() {
    name = "Triggered";
  stateLED[0] = greenLED;
  stateLED[1] = redLED;
  stateLED[2] = yellowLED;
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
  //timer->Start(StaticTimerFunction, sprayDelay);  // use recursive function to call 'count' times
}

static void Triggered::StaticTimerFunction() {
  //Triggered::instance->TimerFunction();
}

void Triggered::TimerFunction() {
  /*Spray();
  if (count > 0) {
    timer->Start(StaticTimerFunction, sprayDelay);
  }*/
}

void Triggered::Exit() {
  State::Exit();
  timer->Stop();
  delete Triggered::instance;
  Triggered::instance = nullptr;
}

State& Triggered::Update() {
  //if (count == 0)
  //  return new Idle();
  return *this;
}

void Triggered::Spray() {
  // Do the spray

  // Reduce spray count to do
  count--;
}

// operator menu active
// red + yellow led on
InMenu::InMenu() {
    name = "InMenu";
  stateLED[0] = redLED;
  stateLED[1] = yellowLED;
}

InMenu* InMenu::instance = nullptr;

InMenu* InMenu::GetInstance() {
  if (InMenu::instance == nullptr) {
    InMenu::instance = new InMenu();
  }
  return InMenu::instance;
}

State& InMenu::Update() {
  // Menu action
  /*
    define a bunch of menu actions.
    */
  return *this;
}