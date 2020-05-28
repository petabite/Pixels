#ifndef Pixels_h
#define Pixels_h

#include "Arduino.h"
#include "FastLED.h"

enum Direction {
    LEFT,
    RIGHT
};

class Pixels
{
    public:
        Pixels(CRGB leds_array[], byte num_leds);
        void chase(word delay_ms=20, CRGB color=randomColor(), byte segment_length=1, Direction direction=RIGHT);
        void fillStrip(word delay_ms=25, CRGB color=randomColor());
        void fillFromMiddle(word delay_ms=60, CRGB color=randomColor());
        void fillFromSides(word delay_ms=60, CRGB color=randomColor());
        void randomFill(word delay_ms=150, CRGB color=randomColor());
        void wipe(word delay_ms=50, CRGB color=randomColor());
        void altColors(word delay_ms=125, CRGB first_color=randomColor(), CRGB second_color=randomColor());
        void bounce(word delay_ms=30, byte segment_length=1, CRGB color=randomColor());
        void rgbFade(word delay_ms=3);
        void rainbow(word delay_ms=20, byte iterations=1);
        void rainbowChase(word delay_ms=50);
        void rainbowCycle(word delay_ms=100);
        void sparkle(word delay_ms=10, CRGB color=CRGB::White);
        void meteor(word delay_ms=50, byte length=5, boolean random_decay=true, byte decay_amount=64, CRGB color=randomColor());
        static CRGB randomColor();
        void clear();
        void setStrip(CRGB color);
    private:
        byte* wheel(byte pos);
        word num_leds;
        CRGB *leds;
};

#endif