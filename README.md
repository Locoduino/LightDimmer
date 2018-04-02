# LightDimmer

A LED dimmer library for Arduino

LightDimmer is designed  drive lights of railroad signals.
One or many LED can be driven simultaneously. For each LED
the time needed to switch on the light and the time needed
to switch it off can be specified. The light can also blink
with a specified period.

## Using the library

As usual, you have to include it at the beginning of your sketch:

```
#include <LightDimmer.h>
```

Then you have to instantiate as many object as lights you want to drive.
The fist argument is the pin to which the LED is connected and the
second one can be HIGH or LOW. It is the value to apply to the pin
to switch the LED on. Of course for LightDimmer objects, fading is only
possible on PWM pins.

```
LightDimmer crossingLight;
```

With version 1.1, a LightDimmerSoft soft PWM class has been added. The API
described below stays the same. Instead of having 256 levels, there are only 32.
Performances measured on an Arduino Uno show a PWM frequency of 266 Hz for
12 LED driven simultaneously.

```
LightDimmerSoft secondCrossingLight;
```

By default the period is set to 900ms, the fading and brightening time is set
to 250ms and the on time is set to 200ms. This correspond to blinking lights of french railway lights.

The following functions are available:

### LightDimmer::update()

LightDimmer::update shall be called in loop to allow the library to update the state of each LED. If the call frequency is not high enough you will get discontinuous update in the fading and brightening process for LightDimmer objects (those using hardware PWM). LightDimmerSoft object (those using software PWM) will flicker. So you shall never use the delay function your sketch.

### begin(pin, level)

begin has to be called in setup for each LED. ```pin``` is the pin to which the
LED is connected. ```level``` is the logical level, HIGH or LOW, to light up the LED.

### setFadingTime(time)

Set the time it take to fade the LED from the maximum value to the
minimum value. time is in milliseconds

### setBrighteningTime(time)

Set the time it take to fade the LED from the minimum value to the
maximum value. time is in milliseconds

### setOnTime(time)

Set the time the LED stays on when blinking.

### setPeriod(time)

Set the blinking period. the period should be greater or equal to the sum
of the brightening time, the on time and the fading time. Otherwise, blinking
cannot be done.

### on()

Switch the LED on using the brightening time.

### off()

Switch the LED off using the fading time.

### startBlink()

Starts the blinking provided the condition given in the setPeriod paragraph is fulfilled.

### stopBlink()

Stop the blinking.

### isOn()

Returns true is the LED is currently on

### isOff()

Returns true is the LED is currently off

### isBrightening()

Returns true is the LED is currently brightening

### isFading()

Returns true is the LED is currently fading
