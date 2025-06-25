#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN      4
#define NUMPIXELS 7

int time=5000;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
pixels.begin();
Serial.begin(4800);
}
void loop() {
 pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Red
  pixels.show();
  delay(DELAYVAL);

  pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // Green
  pixels.show();
  delay(DELAYVAL);

  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // Blue
  pixels.show();
  delay(DELAYVAL);

  pixels.setPixelColor(0, pixels.Color(255, 255, 0)); // Yellow
  pixels.show();
  delay(DELAYVAL);

  pixels.setPixelColor(0, pixels.Color(0, 255, 255)); // Cyan
  pixels.show();
  delay(DELAYVAL);

  pixels.setPixelColor(0, pixels.Color(255, 0, 255)); // Magenta
  pixels.show();
  delay(DELAYVAL);

  pixels.setPixelColor(0, pixels.Color(255, 255, 255)); // White
  pixels.show();
  delay(DELAYVAL);
}
