/*
 * In this example 10 LED of a bargraph blink and stack
 */

#include <LightDimmer.h>

LightDimmerSoft led[10];

void setup()
{
  for (uint8_t i = 0; i < 10; i++) {
    led[i].begin(i + 3, HIGH);
  }
}

uint8_t previousMovingLed = 255;
uint8_t movingLed = 0;
uint8_t stackedLed = 9;
uint32_t nextEventDate = 1000;

void loop()
{
  LightDimmer::update();

  if (stackedLed != 255) {
    uint32_t currentDate = millis();
    if (currentDate > nextEventDate) {
      nextEventDate = currentDate + 1000;
  
      if (previousMovingLed != 255) {
        led[previousMovingLed].off();
      }
      previousMovingLed = movingLed;
      led[movingLed].startBlink();
      if (movingLed == stackedLed) {
        stackedLed--;
        movingLed = 0;
        previousMovingLed = 255;
      }
      else {
        movingLed++;
      }
    }
  }
}
