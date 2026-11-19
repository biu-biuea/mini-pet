#pragma once

Adafruit_ST7735 tft = Adafruit_ST7735(&SPI, TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16 canvas(128, 160);   // draw here first, then send it all at once (no flicker)

void setupScreen() {
  SPI.begin(D8, -1, D10, -1);   // clock on d8, data on d10
  tft.initR(INITR_GREENTAB);
  tft.setRotation(0);
  uint8_t madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MY;   // fixes swapped colors
  tft.sendCommand(ST77XX_MADCTL, &madctl, 1);
  canvas.setTextWrap(false);
}

uint16_t colorFor(char p) {
  switch (p) {
    case 'K': return C_OUTLINE;
    case 'B': return C_BODY;
    case 'M': return C_MID;
    case 'S': return C_SHADE;
    case 'L': return C_LIGHT;
    case 'C': return C_CHEEK;
    case 'T': return C_TEAR;
    case 'P': return C_POOP;
    case 'H': return C_HEART;
    case 'W': return C_GHOST;
    case 'G': return C_GHOSTLINE;
  }
  return C_OUTLINE;
}

void drawSprite(const char* rows[], int h, int x, int y, int scale) {
  for (int r = 0; r < h; r++) {
    for (int c = 0; rows[r][c] != '\0'; c++) {
      char p = rows[r][c];
      if (p != '.') canvas.fillRect(x + c * scale, y + r * scale, scale, scale, colorFor(p));
    }
  }
}

void centerText(const char* text, int y, int size, uint16_t color) {
  canvas.setTextSize(size);
  canvas.setTextColor(color);
  int w = strlen(text) * 6 * size;
  canvas.setCursor((128 - w) / 2, y);
  canvas.print(text);
}

void showFrame() {
  tft.drawRGBBitmap(0, 0, canvas.getBuffer(), 128, 160);
}