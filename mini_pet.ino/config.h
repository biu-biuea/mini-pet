#pragma once

// ========================================
// change your pet's name here (about 10 letters max)
const char* PET_NAME = "star";
// ========================================

// true = your board (touch sensor on d5), false = kit boards (pet button on d5)
#define PET_IS_TOUCH true

// screen pins
#define TFT_CS   -1   // cs is wired to gnd
#define TFT_DC   D9
#define TFT_RST  D7

// buttons
#define BTN_FEED  D3   // button a
#define BTN_PLAY  D4   // button b
#define BTN_CLEAN D0   // button c
#define BTN_PET   D5   // pet button (or touch sensor)

// leds and buzzer
#define LED_HAPPY D2
#define LED_ALERT D6
#define BUZZER    D1