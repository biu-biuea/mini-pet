#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// the order matters: each file uses things from the ones above it
#include "config.h"
#include "colors.h"
#include "sprites.h"
#include "screen.h"
#include "sound.h"
#include "pet.h"
#include "buttons.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  setupScreen();
  setupSound();
  setupButtons();
  setupPet();
}

void loop() {
  handleButtons();
  updateStats();
  updateSound();
  updateLightsAndAlerts(getMood());

  static unsigned long lastDraw = 0;
  if (millis() - lastDraw > 80) {
    lastDraw = millis();
    drawEverything();
  }
}