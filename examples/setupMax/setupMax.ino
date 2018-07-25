/*
 * A setupMax example for LightDimmer with the builtin LED.
 *
 * Blinking is started with the default values:
 * - Brightening time equal to 250ms
 * - Fading time equal to 250ms
 * - On time equal to 200ms
 * - Period equal to 900ms
 */

#include <LightDimmer.h>

LightDimmerSoft myLED;

void setup() {
  Serial.begin(115200);
  myLED.begin(13,HIGH);
  myLED.startBlink();
}

uint8_t maxVal = 255;

uint8_t saturationAdd(const uint8_t val, const uint8_t add)
{
  if ((255 - add) < val) return 255;
  else return val + add; 
}

uint8_t saturationSub(const uint8_t val, const uint8_t sub)
{
  if (sub > val) return 0;
  else return val - sub; 
}

void loop() {
  if (Serial.available()) {
    char key = Serial.read();
    switch (key) {
      case 'p': maxVal = saturationAdd(maxVal, 10); myLED.setupMax(maxVal); break;
      case 'o': maxVal = saturationSub(maxVal, 10); myLED.setupMax(maxVal); break;
      case 'b': myLED.startBlink();
    }
  }
  LightDimmer::update();
}
