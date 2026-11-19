#pragma once

const int PIX_SIZE = 5;   // each sprite pixel = 5x5 screen pixels
const uint16_t C_DEAD = COL(205, 200, 195);   // gray body when star dies
int petX, petY;

void dot(int gx, int gy, uint16_t c) {
  canvas.fillRect(petX + gx * PIX_SIZE, petY + gy * PIX_SIZE, PIX_SIZE, PIX_SIZE, c);
}

void drawFace(Mood m) {
  bool blink = (millis() % 3000) < 150;
  uint16_t k = C_OUTLINE;

  // eyes
  if (m == SLEEPY || blink) {
    dot(5,7,k); dot(6,7,k); dot(9,7,k); dot(10,7,k);
  } else if (m == HAPPY) {
    dot(5,7,k); dot(6,6,k); dot(7,7,k); dot(8,7,k); dot(9,6,k); dot(10,7,k);
  } else if (m == UPSET) {
    dot(5,5,k); dot(6,6,k); dot(10,5,k); dot(9,6,k);   // angry brows
    dot(6,7,k); dot(9,7,k);
  } else {
    dot(6,6,k); dot(6,7,k); dot(9,6,k); dot(9,7,k);
  }

  // mouth
  switch (m) {
    case HAPPY:  dot(6,9,k); dot(7,10,k); dot(8,10,k); dot(9,9,k);
                 dot(4,8,C_CHEEK); dot(11,8,C_CHEEK); break;
    case SAD:    dot(6,10,k); dot(7,9,k); dot(8,9,k); dot(9,10,k);
                 dot(10,8,C_TEAR); dot(10,9,C_TEAR); break;
    case UPSET:  dot(6,10,k); dot(7,10,k); dot(8,10,k); dot(9,10,k); break;
    case HUNGRY: dot(7,9,k); dot(8,9,k); dot(7,10,k); dot(8,10,k); break;
    case POTTY:  dot(6,9,k); dot(7,10,k); dot(8,9,k); dot(9,10,k); break;
    case SLEEPY: dot(7,10,k); break;
    default:     dot(7,9,k); dot(8,9,k); break;
  }
}

// little pips in the top right corner: 5 per stat, each one = 20%
void drawPips(int y, int value, uint16_t color, bool triangle) {
  int filled = (value + 19) / 20;   // 0 to 5
  for (int i = 0; i < 5; i++) {
    int x = 78 + i * 10;
    uint16_t c = (i < filled) ? color : C_BARBG;
    if (triangle) canvas.fillTriangle(x, y + 6, x + 3, y, x + 6, y + 6, c);
    else canvas.fillCircle(x + 3, y + 3, 3, c);
  }
}

// star tipped over on his side, in gray
void drawFallenPet(int x, int y) {
  for (int r = 0; r < 16; r++) {
    for (int c = 0; PET_BODY[r][c] != '\0'; c++) {
      char p = PET_BODY[r][c];
      if (p == '.') continue;
      uint16_t col = (p == 'K') ? C_TEXT : C_DEAD;
      // turned 90 degrees: rows become columns
      canvas.fillRect(x + (15 - r) * PIX_SIZE, y + c * PIX_SIZE, PIX_SIZE, PIX_SIZE, col);
    }
  }
}

void drawEverything() {
  Mood m = getMood();
  unsigned long t = millis();

  canvas.fillScreen(C_BG);

  drawPips(4, food, C_FOOD, false);   // circles
  drawPips(14, fun, C_FUN, true);     // triangles
  drawPips(24, rest, C_REST, false);  // circles

  petX = 24;   // centered: (128 - 80) / 2

  if (dead) {
    petY = 40;
    drawFallenPet(petX, petY);
    int rise = ((t - deadAt) / 40) % 60;           // ghost floats up, then repeats
    int sway = ((t / 300) % 2) ? 2 : -2;
    drawSprite(GHOST, 10, 49 + sway, 60 - rise, 3);
  } else {
    // star bobs up and down (slower when asleep)
    int bobSpeed = asleep ? 1000 : 450;
    petY = 36 + ((t / bobSpeed) % 2 ? 3 : 0);
    drawSprite(PET_BODY, 16, petX, petY, PIX_SIZE);
    drawFace(m);

    if (t < pettedUntil) drawSprite(HEART, 6, 100, 34 + ((t / 200) % 2) * 2, 3);

    if (asleep) {
      canvas.setTextColor(C_REST);
      canvas.setTextSize(1 + (t / 600) % 2);
      canvas.setCursor(106, 38);
      canvas.print("z");
    }

    for (int i = 0; i < poops; i++) {
      int px = (i == 1) ? 110 : 2;
      int py = (i == 2) ? 80 : 100;
      drawSprite(POOP, 7, px, py, 2);
    }
  }

  centerText(PET_NAME, 124, 2, C_TEXT);
  const char* bottom = (t < messageUntil) ? message : MOOD_NAMES[m];
  centerText(bottom, 146, 1, C_TEXT);

  showFrame();
}