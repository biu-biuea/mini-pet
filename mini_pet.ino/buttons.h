#pragma once

const int BUTTONS[4] = { BTN_FEED, BTN_PLAY, BTN_CLEAN, BTN_PET };
bool lastState[4] = { false, false, false, false };   // true = being pressed
unsigned long lastChange[4] = { 0, 0, 0, 0 };

void setupButtons() {
  for (int i = 0; i < 3; i++) pinMode(BUTTONS[i], INPUT_PULLUP);
  pinMode(BTN_PET, PET_IS_TOUCH ? INPUT : INPUT_PULLUP);
}

// buttons read LOW when pressed, the touch sensor reads HIGH when touched
bool isDown(int i) {
  bool level = digitalRead(BUTTONS[i]);
  if (i == 3 && PET_IS_TOUCH) return level == HIGH;
  return level == LOW;
}

// true once each time a button gets pressed down
bool justPressed(int i) {
  bool down = isDown(i);
  if (down != lastState[i] && millis() - lastChange[i] > 40) {
    lastChange[i] = millis();
    lastState[i] = down;
    return down;
  }
  return false;
}

void handleButtons() {
  for (int i = 0; i < 4; i++) {
    if (justPressed(i)) {
      if (dead) { if (millis() - deadAt > 2000) resetPet(); continue; }
      if (asleep) { say("shh... zzz"); continue; }
      if (i == 0) feed();
      if (i == 1) play();
      if (i == 2) cleanUp();
      if (i == 3) pet();
    }
  }
}