#pragma once

struct Note { int freq; int ms; };   // freq 0 = short silence

const Note TUNE_HELLO[] = { {523, 90}, {659, 90}, {784, 90}, {1047, 150} };
const Note TUNE_FEED[]  = { {880, 60}, {0, 30}, {1175, 80} };
const Note TUNE_PLAY[]  = { {784, 80}, {988, 80}, {1175, 80}, {1568, 120} };
const Note TUNE_CLEAN[] = { {1568, 50}, {1319, 50}, {1047, 50}, {784, 80} };
const Note TUNE_PET[]   = { {1047, 40}, {1319, 40}, {1568, 60} };
const Note TUNE_ALERT[] = { {1760, 100}, {0, 80}, {1760, 100} };
const Note TUNE_SLEEP[] = { {659, 120}, {523, 120}, {392, 200} };
const Note TUNE_DIE[]   = { {784, 200}, {740, 200}, {698, 200}, {659, 400} };

Note queue[12];
int queueLen = 0;
int queuePos = 0;
unsigned long noteEnds = 0;

void setupSound() {
  pinMode(BUZZER, OUTPUT);
}

void playTune(const Note* notes, int count) {
  queueLen = min(count, 12);
  for (int i = 0; i < queueLen; i++) queue[i] = notes[i];
  queuePos = 0;
  noteEnds = 0;
}
#define TUNE(t) playTune(t, sizeof(t) / sizeof(Note))

void updateSound() {
  if (queuePos >= queueLen || millis() < noteEnds) return;
  Note n = queue[queuePos++];
  if (n.freq > 0) tone(BUZZER, n.freq, n.ms);
  noteEnds = millis() + n.ms + 15;
}