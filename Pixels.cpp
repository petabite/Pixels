#include "Pixels.h"
#include "FastLED.h"

Pixels::Pixels(CRGB leds[], byte num_leds)
: leds(leds), num_leds(num_leds)
{
    clear();
    randomSeed(analogRead(A0));
}

void Pixels::chase(word delay_ms, CRGB color, byte segment_length, Direction direction) {
    switch (direction)
    {
    case LEFT:
        for (int i = num_leds-segment_length-2; i > 0; i--) {
            clear();
            leds[i].setRGB(color.r/10, color.g/10, color.b/10);
            for (int j = 1; j <= segment_length; j++) {
                leds[i+j] = color;
            }     
            leds[i+segment_length+1].setRGB(color.r/10, color.g/10, color.b/10);
            FastLED.show();
            delay(delay_ms);   
        }
        break;
    case RIGHT:
        for (int i = 0; i < num_leds-segment_length-2; i++) {
            clear();
            leds[i].setRGB(color.r/10, color.g/10, color.b/10);
            for (int j = 1; j <= segment_length; j++) {
                leds[i+j] = color;
            }     
            leds[i+segment_length+1].setRGB(color.r/10, color.g/10, color.b/10);
            FastLED.show();
            delay(delay_ms); 
        }
        break;
    }
}

void Pixels::fillStrip(word delay_ms, CRGB color) {
    byte counter = num_leds;
    while (counter > 0) {
        for (byte i = 0; i < counter; i++) {
            leds[i] = color;
            FastLED.show();
            delay(delay_ms);
            if (i != counter-1) leds[i] = CRGB::Black;
        }
        counter--;
    }
}

void Pixels::fillFromMiddle(word delay_ms, CRGB color) {
    byte midpoint = num_leds / 2;
    byte counter = 0;
    while (counter != midpoint) {
        leds[midpoint + counter] = color; // left side
        if (num_leds % 2 == 0) {
            leds[midpoint - 1 - counter] = color; //right side for even number strips
        } else {
            leds[midpoint - counter] = color; //right side for odd number strips
        }
        FastLED.show();
        delay(delay_ms);
        counter++;
    }
}

void Pixels::fillFromSides(word delay_ms, CRGB color) {
    byte midpoint = (byte) num_leds/2;
    byte counter = 0;
    while (counter != midpoint) {
        leds[counter] = color;
        leds[num_leds - 1 - counter] = color;
        FastLED.show();
        delay(delay_ms);
        counter++;
    }
}

void Pixels::randomFill(word delay_ms, CRGB color) {
    // generate random leds indices
    byte led_indices[num_leds];
    for (byte i = 0; i < num_leds; i++){
        led_indices[i] = i;
    }
    for (byte i = 0; i < num_leds; i++){
        byte rand_i = random(0, num_leds);
        byte temp = led_indices[i];
        led_indices[i] = led_indices[rand_i];
        led_indices[rand_i] = temp;
    }
    for (byte i = 0; i < num_leds; i++){
        leds[led_indices[i]] = color;
        FastLED.show();
        delay(delay_ms);   
    }
}

void Pixels::wipe(word delay_ms, CRGB color) {
    while (1) {
        for (byte i = 0; i < num_leds; i ++) {
            leds[i] = color;
            FastLED.show();
            delay(delay_ms);
        }
        for (byte i = 0; i < num_leds; i ++) {
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(delay_ms);
        }
    }
}

void Pixels::altColors(word delay_ms, CRGB first_color, CRGB second_color) {
    while (1) {
        for (byte i = 0; i < num_leds; i++) {
            if (i % 2 == 0)
                leds[i] = first_color;
            else
                leds[i] = second_color;
        }
        FastLED.show();
        delay(delay_ms);
        for (byte i = 0; i < num_leds; i++) {
            if (i % 2 == 0)
                leds[i] = second_color;
            else
                leds[i] = first_color;
        }
        FastLED.show();
        delay(delay_ms);
    }
}

void Pixels::bounce(word delay_ms, byte segment_length, CRGB color) {
    while (1) {
        chase(delay_ms, color, segment_length, RIGHT);
        chase(delay_ms, color, segment_length, LEFT);
    }
}

void Pixels::rgbFade(word delay_ms) {
    for(int j = 0; j < 3; j++ ) {
        // IN
        for(int k = 0; k < 256; k++) {
            switch(j) {
                case 0: setStrip(CRGB(k,0,0)); break;
                case 1: setStrip(CRGB(0,k,0)); break;
                case 2: setStrip(CRGB(0,0,k)); break;
            }
            FastLED.show();
            delay(delay_ms);
        }
        // OUT
        for(int k = 255; k >= 0; k--) {
            switch(j) {
                case 0: setStrip(CRGB(k,0,0)); break;
                case 1: setStrip(CRGB(0,k,0)); break;
                case 2: setStrip(CRGB(0,0,k)); break;
            }
            FastLED.show();
            delay(delay_ms);
        }
    }
}

void Pixels::rainbow(word delay_ms, byte iterations) {
    byte *c;
    for (byte j = 0; j < 256*iterations; j++) {
        for (byte i = 0; i < num_leds; i++) {
            c = wheel(((int)(i*256 / num_leds) + j) & 255);
            leds[i].setRGB(*c, *(c+1), *(c+2));
        }
        FastLED.show();
        delay(delay_ms);
    }
}

void Pixels::rainbowChase(word delay_ms) {
    byte *c;
    for (byte j = 0; j < 256; j++) {
        for (byte q = 0; q < 3; q++) {
            for (byte i = 0; i < num_leds; i+=3) {
                c = wheel((i + j) % 255);
                leds[i+q].setRGB(*c, *(c+1), *(c+2));
            }
            FastLED.show();
            delay(delay_ms);
            for (byte i = 0; i < num_leds; i+=3) {
                leds[i+q] = CRGB::Black;
            }
        }
    }
}

void Pixels::rainbowCycle(word delay_ms) {
    while (1) {
        for (int k = 0; k < 256; k++){
            for (byte i = 0; i < num_leds; i++) {
                leds[i].setHue(k);
            }
            FastLED.show();
            delay(delay_ms);
        }
    }
}

void Pixels::sparkle(word delay_ms, CRGB color) {
    while (1)
    {
        byte i = random(0, num_leds);
        leds[i] = color;
        FastLED.show();
        delay(delay_ms);
        leds[i] = CRGB::Black;
    }
}

void Pixels::clear() {
    setStrip(CRGB::Black);
}

void Pixels::setStrip(CRGB color) {
    for (byte i = 0; i < num_leds; i++) {
        leds[i] = color;
    }
    FastLED.show();
}

void Pixels::meteor(word delay_ms, byte length, boolean random_decay, byte decay_amount, CRGB color) {
    for (word i = 0; i < num_leds*2; i++) {
      for (byte j = 0; j < num_leds; j++) {
        if (!random_decay || random(0, 10) > 5)
          leds[j].fadeToBlackBy(decay_amount);
      }
      for(int j = 0; j < length; j++) {
        if ((i-j < num_leds) && (i-j >= 0))
          leds[i-j] = color;
      }
      FastLED.show();
      delay(delay_ms);
    }
}

byte* Pixels::wheel(byte pos) {
    static byte c[3];
    if (pos < 85) {
        c[0]=pos * 3;
        c[1]=255 - pos * 3;
        c[2]=0;
    } else if (pos < 170) {
        pos -= 85;
        c[0]=255 - pos * 3;
        c[1]=0;
        c[2]=pos * 3;
    } else {
        pos -= 170;
        c[0]=0;
        c[1]=pos * 3;
        c[2]=255 - pos * 3;
    }
    return c;
}

CRGB Pixels::randomColor() {
    return CRGB(random(0, 256), random(0, 256), random(0, 256));
}