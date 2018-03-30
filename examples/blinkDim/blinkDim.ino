/*
 * A very simple example for LightDimmer with a PWM pin.
 *
 * Blinking is started with the default values:
 * - Brightening time equal to 250ms
 * - Fading time equal to 250ms
 * - On time equal to 200ms
 * - Period equal to 900ms
 */

#include <LightDimmer.h>

LightDimmer myLED;

void setup() {
  myLED.begin(6,HIGH);
  myLED.startBlink();
}

void loop() {
  LightDimmer::update();
}
