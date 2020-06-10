<h1>Pixels</h1>

**WS2812 RGB LED Strip Controller for Arduino**

<h2>Contents</h2>

- [Features](#features)
- [Changelog](#changelog)
- [Materials](#materials)
- [Dependencies](#dependencies)
- [Schematic](#schematic)
- [Setup](#setup)
- [Quick Start](#quick-start)
- [Documentation](#documentation)
  - [Constructor](#constructor)
  - [`Pixels(CRGB leds_array[], byte num_leds)`](#pixelscrgb-leds_array-byte-num_leds)
        - [Description](#description)
        - [Parameters](#parameters)
  - [Members](#members)
  - [`void chase(word delay_ms=20, CRGB color=randomColor(), byte segment_length=1, Direction direction=RIGHT)`](#void-chaseword-delay_ms20-crgb-colorrandomcolor-byte-segment_length1-direction-directionright)
        - [Description](#description-1)
        - [Parameters](#parameters-1)
  - [`void fillStrip(word delay_ms=25, CRGB color=randomColor())`](#void-fillstripword-delay_ms25-crgb-colorrandomcolor)
        - [Description](#description-2)
        - [Parameters](#parameters-2)
  - [`void fillFromMiddle(word delay_ms=60, CRGB color=randomColor())`](#void-fillfrommiddleword-delay_ms60-crgb-colorrandomcolor)
        - [Description](#description-3)
        - [Parameters](#parameters-3)
  - [`void fillFromSides(word delay_ms=60, CRGB color=randomColor())`](#void-fillfromsidesword-delay_ms60-crgb-colorrandomcolor)
        - [Description](#description-4)
        - [Parameters](#parameters-4)
  - [`void randomFill(word delay_ms=150, CRGB color=randomColor())`](#void-randomfillword-delay_ms150-crgb-colorrandomcolor)
        - [Description](#description-5)
        - [Parameters](#parameters-5)
  - [`void wipe(word delay_ms=50, CRGB color=randomColor())`](#void-wipeword-delay_ms50-crgb-colorrandomcolor)
        - [Description](#description-6)
        - [Parameters](#parameters-6)
  - [`void altColors(word delay_ms=125, CRGB first_color=randomColor(), CRGB second_color=randomColor())`](#void-altcolorsword-delay_ms125-crgb-first_colorrandomcolor-crgb-second_colorrandomcolor)
        - [Description](#description-7)
        - [Parameters](#parameters-7)
  - [`void bounce(word delay_ms=30, byte segment_length=1, CRGB color=randomColor())`](#void-bounceword-delay_ms30-byte-segment_length1-crgb-colorrandomcolor)
        - [Description](#description-8)
        - [Parameters](#parameters-8)
  - [`void rgbFade(word delay_ms=3)`](#void-rgbfadeword-delay_ms3)
        - [Description](#description-9)
        - [Parameters](#parameters-9)
  - [`void rainbow(word delay_ms=20, byte iterations=1)`](#void-rainbowword-delay_ms20-byte-iterations1)
        - [Description](#description-10)
        - [Parameters](#parameters-10)
  - [`void rainbowChase(word delay_ms=50)`](#void-rainbowchaseword-delay_ms50)
        - [Description](#description-11)
        - [Parameters](#parameters-11)
  - [`void rainbowCycle(word delay_ms=100)`](#void-rainbowcycleword-delay_ms100)
        - [Description](#description-12)
        - [Parameters](#parameters-12)
  - [`void sparkle(word delay_ms=10, CRGB color=CRGB::White)`](#void-sparkleword-delay_ms10-crgb-colorcrgbwhite)
        - [Description](#description-13)
        - [Parameters](#parameters-13)
  - [`void meteor(word delay_ms=50, byte length=5, boolean random_decay=true, byte decay_amount=64, CRGB color=randomColor())`](#void-meteorword-delay_ms50-byte-length5-boolean-random_decaytrue-byte-decay_amount64-crgb-colorrandomcolor)
        - [Description](#description-14)
        - [Parameters](#parameters-14)
  - [`static CRGB randomColor()`](#static-crgb-randomcolor)
        - [Description](#description-15)
        - [Returns](#returns)
  - [`void clear()`](#void-clear)
        - [Description](#description-16)
  - [`void setStrip(CRGB color)`](#void-setstripcrgb-color)
        - [Description](#description-17)
        - [Parameters](#parameters-15)
- [Additional Resources](#additional-resources)

## Features

- Two buttons for control
- Current animation resumes even after power cycle
- Use the library by itself or with the controller sketch
- Built with FastLED library

## Changelog

| Release |             Changes             |   Date    |
| :-----: | :-----------------------------: | :-------: |
|  v1.0   | <ul><li>First release</li></ul> | 6/10/2020 |

## Materials

- Any Arduino-compatible board(ex: Arduino Pro Mini, SparkFun Pro Micro)
- WS2812b Individually Addressable RGB LEDs
- 270 ohm resistor
- 1000 μF capacitor
- 5V Power Supply(The amperage depends on your project. Each LED draws about 60mA @ full brightness/completely white)
- FTDI USB to Serial Converter (for programming your board if it doesn't have USB support, such as for the Pro Mini)

## Dependencies

- FastLED library(from [here](https://github.com/FastLED/FastLED))
- EEPROM library(should already be included with Arduino IDE)

## Schematic

**possible setup on a breadboard**

![breadboard layout](https://raw.githubusercontent.com/petabite/Pixels/master/docs/pixels.png)

## Setup

1. Set up a circuit like above
2. Download Pixels from releases tab
3. Edit `Pixels.ino`

   - Edit the macro definitions at the top of `Pixels.ino` for your specific setup

   ```cpp
   #define NUM_LEDS 30 // <- the number of leds in your strip
   #define PIN 10 // <- the pin on your board you want to use for data

   #define NEXT_ANIMATION_PIN 2 // <- the pin your next animation button is attached to
   #define ON_OFF_PIN 3 // <-  the pin your on/off button is attached to

   ```

4. Upload `Pixels.ino` to your board
5. Power up your board and LED strip
6. Enjoy!

## Quick Start

**if you want to use Pixels by itself**

```cpp


void setup() {
    // init Pixels
    CRGB leds[NUM_LEDS];
    FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
    Pixels pixels(leds, NUM_LEDS);
    pixels.chase(20, CRGB(150, 0, 0), 5, LEFT);
    ...
}

void loop() {

}

```

## Documentation

### Constructor

### `Pixels(CRGB leds_array[], byte num_leds)`

###### Description

Initialize a Pixels object

###### Parameters

- leds_array - (CRGB[]) CRGB array declared with a size of `num_leds`
- num_leds - (byte) number of LEDS on strip

---

### Members

### `void chase(word delay_ms=20, CRGB color=randomColor(), byte segment_length=1, Direction direction=RIGHT)`

###### Description

Chase animation going left or right

###### Parameters

- delay_ms - (word) delay in ms
- color - (CRGB) RGB color for animation
- segment_length - (byte) length of segment
- direction - (Direction) direction of animation

---

### `void fillStrip(word delay_ms=25, CRGB color=randomColor())`

###### Description

Fill strip animation starting from the first LED

###### Parameters

- delay_ms - (word) delay in ms
- color - (CRGB) RGB color for animation

---

### `void fillFromMiddle(word delay_ms=60, CRGB color=randomColor())`

###### Description

Fill strip animation starting from the middle of the strip

###### Parameters

- delay_ms - (word) delay in ms
- color - (CRGB) RGB color for animation

---

### `void fillFromSides(word delay_ms=60, CRGB color=randomColor())`

###### Description

Fill strip animation starting from both ends

###### Parameters

- delay_ms - (word) delay in ms
- color - (CRGB) RGB color for animation

---

### `void randomFill(word delay_ms=150, CRGB color=randomColor())`

###### Description

Random filling of strip one LED at a time

###### Parameters

- delay_ms - (word) delay in ms
- color - (CRGB) RGB color for animation

---

### `void wipe(word delay_ms=50, CRGB color=randomColor())`

###### Description

Color wipe animation across entire strip

###### Parameters

- delay_ms - (word) delay in ms
- color - (CRGB) RGB color for animation

---

### `void altColors(word delay_ms=125, CRGB first_color=randomColor(), CRGB second_color=randomColor())`

###### Description

Alternating colors every other LED on strip

###### Parameters

- delay_ms - (word) delay in ms
- first_color - (CRGB) first RGB color for animation
- second_color - (CRGB) second RGB color for animation

---

### `void bounce(word delay_ms=30, byte segment_length=1, CRGB color=randomColor())`

###### Description

Bouncing animation of one LED from left to right and back

###### Parameters

- delay_ms - (word) delay in ms
- segment_length - (byte) length of segment
- color - (CRGB) RGB color for animation

---

### `void rgbFade(word delay_ms=3)`

###### Description

Fade of RGB values on whole strip

###### Parameters

- delay_ms - (word) delay in ms

---

### `void rainbow(word delay_ms=20, byte iterations=1)`

###### Description

Cycle of colors in rainbow over entire strip

###### Parameters

- delay_ms - (word) delay in ms
- iterations - (byte) repetitions of animation

---

### `void rainbowChase(word delay_ms=50)`

###### Description

Rainbow chase animation

###### Parameters

- delay_ms - (word) delay in ms

---

### `void rainbowCycle(word delay_ms=100)`

###### Description

Cycle through rainbow hue spectrum over entire strip

###### Parameters

- delay_ms - (word) delay in ms

---

### `void sparkle(word delay_ms=10, CRGB color=CRGB::White)`

###### Description

Flashing random LEDs to create sparkling effect

###### Parameters

- delay_ms - (word) delay in ms
- color - (CRGB) RGB color for animation

---

### `void meteor(word delay_ms=50, byte length=5, boolean random_decay=true, byte decay_amount=64, CRGB color=randomColor())`

###### Description

Meteor rain animation

###### Parameters

- delay_ms - (word) delay in ms
- length - (byte) length of meteor
- random_decay - (boolean) allow meteor trail or just keep as solid color
- decay_amount - (byte) how much trail should decay expressed as fraction of 256. ex: 25% = 64/256
- color - (CRGB) RGB color for animation

---

### `static CRGB randomColor()`

###### Description

Generate a random CRGB color

###### Returns

- (CRGB) - random color

---

### `void clear()`

###### Description

Clear entire strip(set each LED to black)

---

### `void setStrip(CRGB color)`

###### Description

Set entire strip to a color

###### Parameters

- color - (CRGB) RGB color to set strip to

---

## Additional Resources

- [FastLED Reference](https://github.com/FastLED/FastLED/wiki/Pixel-reference)
