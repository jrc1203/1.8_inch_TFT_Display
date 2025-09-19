#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Pin definitions for ESP32-S3
#define TFT_CS    10  // Chip Select
#define TFT_RST   11   // Reset
#define TFT_DC    9   // Data/Command
#define TFT_MOSI  12  // SPI MOSI (SDA)
#define TFT_SCLK  13  // SPI Clock (SCL)

// Create display object
// For ST7735-based 1.8" displays
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32-S3 with 1.8\" TFT Display Test");
  
  // Initialize the display
  tft.initR(INITR_BLACKTAB);   // Initialize ST7735S chip, black tab
  
  // Alternative initialization for different variants:
  // tft.initR(INITR_GREENTAB); // for green tab displays
  // tft.initR(INITR_REDTAB);   // for red tab displays
  // tft.initR(INITR_144GREENTAB); // for 1.44" displays
  
  Serial.println("Display initialized");
  
  // Set rotation (0-3)
  tft.setRotation(1); // Landscape mode
  
  // Clear screen
  tft.fillScreen(ST77XX_BLACK);
  
  // Test basic functionality
  testDisplay();
}

void loop() {
  // Demo animations
  colorTest();
  delay(2000);
  
  textTest();
  delay(2000);
  
  shapeTest();
  delay(2000);
  
  bitmapTest();
  delay(2000);
}

void testDisplay() {
  // Display basic info
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("ESP32-S3 TFT Test");
  tft.println("128x160 Display");
  tft.println("ST7735 Controller");
  
  delay(2000);
}

void colorTest() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Color Test");
  
  // Draw colored rectangles
  tft.fillRect(10, 40, 30, 20, ST77XX_RED);
  tft.fillRect(50, 40, 30, 20, ST77XX_GREEN);
  tft.fillRect(90, 40, 30, 20, ST77XX_BLUE);
  
  tft.fillRect(10, 70, 30, 20, ST77XX_YELLOW);
  tft.fillRect(50, 70, 30, 20, ST77XX_MAGENTA);
  tft.fillRect(90, 70, 30, 20, ST77XX_CYAN);
  
  // Color gradient
  for (int i = 0; i < 128; i++) {
    uint16_t color = tft.color565(i * 2, 0, 255 - (i * 2));
    tft.drawFastVLine(i, 100, 20, color);
  }
}

void textTest() {
  tft.fillScreen(ST77XX_BLACK);
  
  // Different text sizes
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("Text Size 1");
  
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_RED);
  tft.println("Size 2");
  
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.println("Small text with");
  tft.println("multiple lines");
  tft.println("for testing");
  
  // Colored text
  tft.setTextColor(ST77XX_YELLOW);
  tft.println("Yellow text");
  tft.setTextColor(ST77XX_CYAN);
  tft.println("Cyan text");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.println("Magenta text");
}

void shapeTest() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("Shape Test");
  
  // Draw shapes
  tft.drawRect(10, 20, 40, 30, ST77XX_RED);
  tft.fillRect(60, 20, 40, 30, ST77XX_GREEN);
  
  tft.drawCircle(30, 80, 15, ST77XX_BLUE);
  tft.fillCircle(80, 80, 15, ST77XX_YELLOW);
  
  tft.drawTriangle(10, 120, 30, 100, 50, 120, ST77XX_MAGENTA);
  tft.fillTriangle(70, 120, 90, 100, 110, 120, ST77XX_CYAN);
  
  // Draw lines
  for (int i = 0; i < 128; i += 10) {
    tft.drawLine(0, 140, i, 160, ST77XX_WHITE);
  }
}

void bitmapTest() {
  tft.fillScreen(ST77XX_BLACK);
  
  // Create a simple bitmap pattern
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("Bitmap Pattern");
  
  // Checkerboard pattern
  for (int x = 0; x < 128; x += 8) {
    for (int y = 20; y < 100; y += 8) {
      if ((x/8 + y/8) % 2 == 0) {
        tft.fillRect(x, y, 8, 8, ST77XX_BLUE);
      } else {
        tft.fillRect(x, y, 8, 8, ST77XX_RED);
      }
    }
  }
  
  // Animation effect
  for (int i = 0; i < 50; i++) {
    int x = random(128);
    int y = random(120, 160);
    tft.drawPixel(x, y, ST77XX_WHITE);
  }
}

// Additional utility functions

void displaySensorData() {
  // Example function to display sensor readings
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("Sensor Data:");
  
  tft.setTextColor(ST77XX_GREEN);
  tft.print("Temperature: ");
  tft.print(25.6);
  tft.println(" C");
  
  tft.setTextColor(ST77XX_BLUE);
  tft.print("Humidity: ");
  tft.print(65.2);
  tft.println(" %");
  
  tft.setTextColor(ST77XX_YELLOW);
  tft.print("Pressure: ");
  tft.print(1013.25);
  tft.println(" hPa");
}

void displayMenu() {
  // Example menu display
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(20, 10);
  tft.println("MENU");
  
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(10, 40);
  tft.println("1. Sensors");
  
  tft.setTextColor(ST77XX_BLUE);
  tft.setCursor(10, 60);
  tft.println("2. Settings");
  
  tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(10, 80);
  tft.println("3. About");
  
  tft.setTextColor(ST77XX_RED);
  tft.setCursor(10, 100);
  tft.println("4. Exit");
}

// Touch screen support (if available)
void handleTouch() {
  // Placeholder for touch functionality
  // You would read touch coordinates here
  // and respond accordingly
}

// Power management
void enterSleepMode() {
  // Turn off display backlight if controllable
  // Put ESP32-S3 into light sleep
  tft.fillScreen(ST77XX_BLACK);
  esp_light_sleep_start();
}

void wakeUp() {
  // Reinitialize display after wake up
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
}