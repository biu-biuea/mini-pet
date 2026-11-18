#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// which xiao pins the screen uses
#define TFT_CS   -1   // cs is wired to gnd, so no pin needed
#define TFT_DC   D9
#define TFT_RST  D7

Adafruit_ST7735 tft = Adafruit_ST7735(&SPI, TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

  // start the screen's data line: clock on d8, data on d10
  SPI.begin(D8, -1, D10, -1);

  tft.initR(INITR_GREENTAB);   // this screen's variant
  tft.setRotation(0);          // upright (portrait)

  // fix the swapped red/blue colors on this screen
  uint8_t madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MY;
  tft.sendCommand(ST77XX_MADCTL, &madctl, 1);

  tft.fillScreen(ST77XX_BLACK);

  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(4, 20);
  tft.println("hi leah!");

  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(4, 50);
  tft.println("pet online");

  tft.fillCircle(64, 110, 15, ST77XX_YELLOW);
}

void loop() {
}