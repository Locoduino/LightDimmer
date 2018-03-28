/*
 * A very simple example for LightDimmer.
 * 
 * Blinking is started with the default values:
 * - Brightening time equal to 250ms
 * - Fading time equal to 250ms
 * - On time equal to 200ms
 * - Period equal to 900ms
 */
 
#include <LightDimmer.h>

LightDimmer myLED (6,LOW);

void setup() {
  myLED.begin();
  myLED.startBlink();
}

void loop() {
  LightDimmer::update();
}
