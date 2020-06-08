#include "Pixels.h"
#include "FastLED.h"
#include "EEPROM.h"

#define NUM_LEDS 30
#define PIN 10

boolean on;
byte current_animation;
void setup() {
  // init Pixels
  CRGB leds[NUM_LEDS];
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  Pixels pixels(leds, NUM_LEDS);
  // get on/off byte from EEPROM
  on = EEPROM.read(1);
  // get current animation from EEPROM
  current_animation = EEPROM.read(0);
  // init EEPROM if it's a new board
  if (current_animation == 255)
    current_animation = 0;
    EEPROM.update(0, current_animation);
  if (on == 255)
    on = 1;
    EEPROM.update(1, on);
  // config interrupt pins
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), nextAnimation, FALLING);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), toggleOnOff, FALLING);
  // don't do anything if off
  while(!on);
  // loop the selected animation
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

// interrupt vars
static unsigned long last_interrupt_time = 0;
unsigned long interrupt_time;
#define INTERRUPT_DELAY 300

void toggleOnOff() {
  interrupt_time = millis();
  // debounce the interrupt
  if (interrupt_time - last_interrupt_time > INTERRUPT_DELAY)
  {
    on = !on;
    //save to EEPROM
    EEPROM.update(1, on);
    // assembly to jump to beginning of code(basically like pressing reset button)
    asm volatile ("  jmp 0");
  }
  last_interrupt_time = interrupt_time;
}

void nextAnimation() {
  interrupt_time = millis();
  // debounce the interrupt
  if (interrupt_time - last_interrupt_time > INTERRUPT_DELAY)
  {
    current_animation++;
    //reset saved animation if past max
    if (current_animation > 12)
      EEPROM.update(0, 0);
    else
      EEPROM.update(0, current_animation);
    // assembly to jump to beginning of code(basically like pressing reset button)
    asm volatile ("  jmp 0");
  }
  last_interrupt_time = interrupt_time;
}

void loop() {

}
