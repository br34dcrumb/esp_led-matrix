#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_IS31FL3731.h"

#define I2C_SDA_PIN 17
#define I2C_SCL_PIN 18

Adafruit_IS31FL3731 ledMatrix = Adafruit_IS31FL3731();

// void drawCustomPixel(int x, int y, uint8_t brightness) {
//     if (x < 8) {
//         ledMatrix.drawPixel(y, x, brightness);  
//     } else {
//         int temp_y = y;
//         x = x - 8;
//         y = 7 - x;
//         x = 7 - temp_y;
//         x = x + 8;
//         ledMatrix.drawPixel(x, y, brightness);  
//     }
// }

// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};

void setup() {
  Serial.begin(9600);
  Serial.println("ISSI swirl test");
  
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  if (! ledMatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");
}

void loop() {
  // animate over all the pixels, and set the brightness from the sweep table
  for (uint8_t incr = 0; incr < 24; incr++)
    for (uint8_t x = 0; x < 16; x++)
      for (uint8_t y = 0; y < 8; y++)
        ledMatrix.drawPixel(x, y, sweep[(x+y+incr)%24]);
  delay(20);
}

