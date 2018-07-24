# LightDimmer

A LED dimmer library for Arduino

LightDimmer is designed to drive lights of railroad signals.
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
described below stays the same. Instead of having 256 levels, there are only 32 which is enough for this kind of application.
Performances measured on an Arduino Uno show a PWM frequency of 263 Hz for
12 LED driven simultaneously.

```
LightDimmerSoft secondCrossingLight;
```

By default the period is set to 900ms, the fading and brightening time is set
to 250ms and the on time is set to 200ms. This correspond to blinking lights of french railway lights.

In ```setup```, you shall call ```begin``` to start each LightDimmer and LightDimmerSoft objects. You can also set the fading and brightening time, the on time and the period for blinking process. See below.

In ```loop```, you shall call ```LightDimmer::update()``` to call the library so that it update the state of each declared object.

### Limitations

Period, on, brightening and fading times are 16 bits integer. So the maximum values of the time settings are 65,535s.

## Functions of LightDimmer

The following functions are available:

### LightDimmer::update()

LightDimmer::update shall be called in loop to allow the library to update the state of each LED. If the call frequency is not high enough you will get discontinuous update in the fading and brightening process for LightDimmer objects (those using hardware PWM). LightDimmerSoft object (those using software PWM) will flicker. So you shall never use the delay function in your sketch.

### LightDimmer::update(howMany)

As an option, update can take as argument the number of objects to update. This allows you to more finely interlace LightDimmer's work and the rest of your sketch. Passing a number of objects greater than the number of objects declared has no particular effect other than updating several times and unnecessarily the same object.

### begin(pin, level)

begin has to be called in setup for each LED. ```pin``` is the pin to which the
LED is connected. ```level``` is the logical level, HIGH or LOW, to light up the LED.

### setMax(max)

```max``` is a 8 bits integer (```uint8_t``` or ```byte```). ```setMax``` sets the duty cycle to set the LED on. setMax allows to adjust the brightness of each LED of your signal without changing the resistor.

### setFadingTime(time)

Set the time it take to fade the LED from the maximum value to the
minimum value. time is in milliseconds and ranges from 1 to 65535.

### setBrighteningTime(time)

Set the time it take to fade the LED from the minimum value to the
maximum value. time is in milliseconds and ranges from 1 to 65535.

### setOnTime(time)

Set the time the LED stays on when blinking. time is in milliseconds and ranges from 0 to 65535.

### setPeriod(time)

Set the blinking period. the period should be greater or equal to the sum
of the brightening time, the on time and the fading time. Otherwise, blinking
cannot be done. time is in milliseconds and ranges from 2 to 65535.

### setupMax(max)

```max``` is a 8 bits integer (```uint8_t``` or ```byte```). ```setupMax``` turns the output on, sets the current value on and sets the duty cycle to set the LED on. setupMax allows to live adjust the brightness of each LED of your signal without changing the resistor.

### on()

Switch the LED on using the brightening time.

### off()

Switch the LED off using the fading time.

### startBlink()

Starts the blinking provided the condition given in the setPeriod paragraph is fulfilled.

### stopBlink()

Stop the blinking.

### isOn()

Returns true if the LED is currently on

### isOff()

Returns true if the LED is currently off

### isBrightening()

Returns true if the LED is currently brightening

### isFading()

Returns true if the LED is currently fading

### isBlinking()

Returns true if the LED is currently blinking

### maximum()

Returns an ```uint8_t``` which is the maximum duty cycle value as set by ```setMax()```

### fadingTime()

Returns an ```uint16_t``` which is the fading time of the LED

### brighteningTime()

Returns an ```uint16_t``` which is the brightening time of the LED

### onTime()

Returns an ```uint16_t``` which is the on time of the LED

### period()

Returns an ```uint16_t``` which is the period of the LED

### pin()

Returns an ```uint8_t``` which is the pin on which the LED is connected

### value()

Returns an ```uint8_t``` which is the current value of the duty cycle
