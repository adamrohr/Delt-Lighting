#include "FastLED.h"

class RainbowScene {
public:
    // FUNCTION TO GET AND SET COLOR
    // THE ORIGINAL FUNCTION WENT BACKWARDS
    // THE MODIFIED FUNCTION SENDS WAVES OUT FROM FIRST LED
    // https://github.com/NeverPlayLegit/Rainbow-Fader-FastLED/blob/master/rainbow.ino
    void rainbow(int react) {
        for(int i = 499; i >= 0; i--) {
            if (i < react)
                leds[i] = Scroll((i * 256 / 50 + k) % 256);
            else
                leds[i] = CRGB(0, 0, 0);      
        }
        FastLED.show(); 
    }

    void setK(int k_in) { k = k_in; }

    void setLEDS(CRGB leds_in[500]) {
        for(int i = 499; i >= 0; --i) {
            leds[i] = leds_in[i];
        }
    }

private:
    // FUNCTION TO GENERATE COLOR BASED ON VIRTUAL WHEEL
    // https://github.com/NeverPlayLegit/Rainbow-Fader-FastLED/blob/master/rainbow.ino
    CRGB Scroll(int pos) {
        CRGB color (0,0,0);
        if(pos < 85) {
            color.g = 0;
            color.r = ((float)pos / 85.0f) * 255.0f;
            color.b = 255 - color.r;
        } else if(pos < 170) {
            color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
            color.r = 255 - color.g;
            color.b = 0;
        } else if(pos < 256) {
            color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
            color.g = 255 - color.b;
            color.r = 0;
        }
        return color;
    }
    
    CRGB leds[500];
    int k = 255;
};