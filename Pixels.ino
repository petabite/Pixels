#include "Pixels.h"
#include "FastLED.h"
#include "EEPROM.h"

#define NUM_LEDS 30
#define PIN 10

byte current_animation;
void setup() {
  // Serial.begin(9600);
  // while (!Serial);
  // init Pixels
  CRGB leds[NUM_LEDS];
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  Pixels pixels(leds, NUM_LEDS);

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), nextAnimation, FALLING);
  current_animation = EEPROM.read(0);
  switch (current_animation)
  {
  case 0:
    pixels.rainbowCycle();  
  case 1:
    while (1)
    {
      pixels.rainbow();    
    }
  case 2:
    pixels.rainbowChase();
  case 3:
    pixels.wipe();
  case 4:
    pixels.bounce(30, 3);
  case 5:
    pixels.altColors();
  case 6:
    while (1)
    {
      pixels.rgbFade();
    }
  case 7:
    while (1) {
      pixels.randomFill();
      pixels.randomFill(150, CRGB::Black);
    }
  case 8:
    while (1)
    {
      pixels.fillFromMiddle();
      pixels.fillFromMiddle(60, CRGB::Black);
    }
  case 9:
    while (1)
    {
      pixels.fillFromSides();
      pixels.fillFromSides(40, CRGB::Black);
    }
    
  case 10:
    while (1)
    {
      pixels.fillStrip(10);
      pixels.meteor(30, 5, true, CRGB::Black);
    }
  case 11:
    pixels.sparkle();
  case 12:
    while (1)
    {
      pixels.meteor();
    }
  }
}

void nextAnimation() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 300)
  {
    current_animation++;
    //reset saved animation if past total
    if (current_animation > 12)
      EEPROM.update(0, 0);
    else
      EEPROM.update(0, current_animation);
    asm volatile ("  jmp 0");
  }
  last_interrupt_time = interrupt_time;
}

void loop() {
  // pixels->chase(20, CRGB(255,0,0), LEFT);
  // pixels->chase(20, CRGB(255,0,0), LEFT);
}
