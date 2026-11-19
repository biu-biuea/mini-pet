#pragma once

enum Mood { HAPPY, NEUTRAL, UPSET, SAD, HUNGRY, SLEEPY, POTTY, DEAD };
const char* MOOD_NAMES[] = { "happy", "neutral", "upset", "sad", "hungry", "sleepy", "needs potty", "rip... tap to restart" };

int food = 80;
int fun = 80;
int rest = 80;
int poops = 0;
bool asleep = false;
bool dead = false;

unsigned long foodTimer = 0, funTimer = 0, restTimer = 0, poopTimer = 0;
unsigned long poopSince = 0;   // when the first poop showed up
unsigned long pettedUntil = 0, messageUntil = 0, alertTimer = 0, deadAt = 0;
const char* message = "";

// how long a dirty potty takes to kill star (milliseconds)
const unsigned long POTTY_LIMIT = 90000;

void say(const char* text) {
  message = text;
  messageUntil = millis() + 1500;
}

void setupPet() {
  pinMode(LED_HAPPY, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);
  poopTimer = millis();
  TUNE(TUNE_HELLO);
}

void resetPet() {
  food = 80; fun = 80; rest = 80; poops = 0;
  asleep = false;
  dead = false;
  poopTimer = millis();
  say("hi again!");
  TUNE(TUNE_HELLO);
}

void die() {
  dead = true;
  asleep = false;
  deadAt = millis();
  TUNE(TUNE_DIE);
}

// ---------- actions ----------
void feed() {
  food = min(100, food + 25);
  say("yum!");
  TUNE(TUNE_FEED);
}

void play() {
  if (rest < 15) { say("too tired..."); return; }
  fun = min(100, fun + 20);
  rest = max(0, rest - 8);
  say("wheee!");
  TUNE(TUNE_PLAY);
}

void cleanUp() {
  if (poops == 0) { say("already clean"); return; }
  poops = 0;
  say("all clean!");
  TUNE(TUNE_CLEAN);
}

void pet() {
  fun = min(100, fun + 5);
  pettedUntil = millis() + 2000;
  say("purr...");
  TUNE(TUNE_PET);
}

// ---------- star slowly needs things over time ----------
void updateStats() {
  if (dead) return;
  unsigned long t = millis();

  if (t - foodTimer > 2000) { foodTimer = t; food = max(0, food - 1); }
  if (t - funTimer > 3000) { funTimer = t; fun = max(0, fun - (poops > 0 ? 2 : 1)); }

  if (asleep) {
    if (t - restTimer > 500) {
      restTimer = t;
      rest = min(100, rest + 2);
      if (rest >= 100) { asleep = false; say("good morning!"); TUNE(TUNE_HELLO); }
    }
  } else if (food == 0) {
    // too hungry to sleep, so rest drains fast
    if (t - restTimer > 1000) { restTimer = t; rest = max(0, rest - 2); }
  } else {
    if (t - restTimer > 4000) { restTimer = t; rest = max(0, rest - 1); }
    if (rest < 10) { asleep = true; TUNE(TUNE_SLEEP); }
  }

  if (!asleep && poops < 3 && t - poopTimer > 40000) {
    poopTimer = t;
    if (poops == 0) poopSince = t;
    poops++;
    say("oops...");
  }

  // the two ways star can die
  if (food == 0 && rest == 0) die();
  if (poops > 0 && t - poopSince > POTTY_LIMIT) die();
}

Mood getMood() {
  if (dead) return DEAD;
  if (asleep) return SLEEPY;
  if (millis() < pettedUntil) return HAPPY;
  if (food < 25) return HUNGRY;
  if (rest < 25) return SLEEPY;
  if (poops > 0) return POTTY;
  if (fun < 30) return SAD;
  if (food < 50 || fun < 50) return UPSET;
  if (food > 70 && fun > 70) return HAPPY;
  return NEUTRAL;
}

void updateLightsAndAlerts(Mood m) {
  unsigned long t = millis();

  if (m == DEAD) {
    digitalWrite(LED_HAPPY, LOW);
    digitalWrite(LED_ALERT, HIGH);
    return;
  }

  digitalWrite(LED_HAPPY, m == HAPPY ? HIGH : LOW);

  bool needsHelp = (m == UPSET || m == SAD || m == HUNGRY || m == POTTY);
  int speed = (m == HUNGRY) ? 150 : 400;
  digitalWrite(LED_ALERT, (needsHelp && (t / speed) % 2) ? HIGH : LOW);

  if (needsHelp && !asleep && t - alertTimer > 20000) {
    alertTimer = t;
    TUNE(TUNE_ALERT);
  }
}