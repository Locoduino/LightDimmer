/*
 * A very simple example for LightDimmer.
 * 
 * The LED is connected to pin 6 so that a HIGH level on pin 6 switches the LED on
 * 
 * Blinking is started with the default values:
 * - Brightening time equal to 250ms
 * - Fading time equal to 250ms
 * - On time equal to 200ms
 * - Period equal to 900ms
 */
 
#include <LightDimmer.h>

LightDimmer myLED (6,HIGH);

void setup() {
  myLED.begin();
  myLED.startBlink();
}

void loop() {
  LightDimmer::update();
}
