/*
 * In this example we change the fading and brightening time and
 * we switch the LED on and off after delays.
 *
 * Note: here delay() can be used because the LED is not fading or brightening
 * when delay() is called.
 */

#include <LightDimmer.h>

LightDimmer led1;

void setup() {
  // put your setup code here, to run once:
  led1.setFadingTime(2000);
  led1.setBrighteningTime(1000);
  led1.begin(6, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  LightDimmer::update();

  if (led1.isOff()) {
    delay(2000);
    led1.on();
  }
  else if (led1.isOn()) {
    delay(2000);
    led1.off();
  }

}
