#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// This file contains our image data array
#include "image.h"

// Pin definitions for ESP32-S3 (Your pins)
#define TFT_CS 10
#define TFT_RST 11
#define TFT_DC 9
#define TFT_MOSI 12
#define TFT_SCLK 13

// ****************** CHANGE 1: Use dimensions from your image.h file ******************
#define IMG_WIDTH  ABDUL_KALAM_4_5_WIDTH  // This was 128
#define IMG_HEIGHT ABDUL_KALAM_4_5_HEIGHT // This was 160

// Create the display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  // Initialize the display driver
  tft.initR(INITR_BLACKTAB);
  Serial.println("Display initialized");

  // Set rotation to Portrait mode (0 for 128x160)
  tft.setRotation(0);

  // Clear the screen to black
  tft.fillScreen(ST77XX_BLACK);

  // ****************** CHANGE 2: Use the CORRECT image name ******************
  tft.drawRGBBitmap(0, 0, (uint16_t*)abdul_kalam_4_5, IMG_WIDTH, IMG_HEIGHT);

  Serial.println("Image should be displayed now.");
}

void loop() {
  // We do nothing in the loop, the image stays on the screen.
  delay(5000);
}