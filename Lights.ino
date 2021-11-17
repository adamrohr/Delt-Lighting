#include "FastLED.h"
//LED LIGHTING SETUP
#define LED_PIN = 6
#define NUM_LEDS = 500
#define BRIGHTNESS = 50
#define LED_TYPE = "WS2811"
#define COLOR_ORDER = "GRB"

CRGB tempLeds[NUM_LEDS];
int scene;

// STANDARD VISUALIZER VARIABLES
int loop_max = 0;
int k = 255; // COLOR WHEEL POSITION
int decay = 10000; // HOW MANY MS BEFORE ONE LIGHT DECAY
int decay_check = 0;
long pre_react = 0; // NEW SPIKE CONVERSION
long litLights = 500; // NUMBER OF LEDs BEING LIT
long post_react = 0; // OLD SPIKE CONVERSION

// RAINBOW WAVE SETTINGS
int wheel_speed = 3;

enum Scenes {
    RAINBOW = 0,
    // PUT THE SCENES YOU DEVELOP BELOW
};

class Lights {

public:
    // DEFAULT: INITIALIZE LIGHTS TO BLACK
    Lights() { 
        for (int i = 0; i < NUM_LEDS; i++)
            leds[i] = CRGB(0, 0, 0);
    }
    // TAKES IN LEDS TO ASSIGN LEDS TO
    Lights(CRGB leds_in[NUM_LEDS]) : leds(leds_in) {}

    // DISPLAYS THE SCENE - ADD YOUR SCENES BELOW
    void displayScene() {
        if(scene == Scenes.RAINBOW) {
            rainbow()
        }
    }

    // GETTER AND SETTER FOR SCENES
    void setScene(Scenes s) { scene = s; }
    Scenes getScene() { return scene; }
    // SETS THE LEDS TO THE INPUT
    void setLEDS(CRGB leds_in[NUM_LEDS]) {
        for(int i = NUM_LEDS - 1; i >= 0; --i) {
            led[i] = leds_in[i];
        }
    }

    // RAINBOW SCENE SPECIFIC FUNCTION
    void setK(int k_in) { k = k_in; }

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              PUT METHODS FOR YOUR LIGHTS IMPLEMENTATION BELOW               *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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

    // FUNCTION TO GET AND SET COLOR
    // THE ORIGINAL FUNCTION WENT BACKWARDS
    // THE MODIFIED FUNCTION SENDS WAVES OUT FROM FIRST LED
    // https://github.com/NeverPlayLegit/Rainbow-Fader-FastLED/blob/master/rainbow.ino
    void rainbow() {
        for(int i = NUM_LEDS - 1; i >= 0; i--) {
            if (i < react)
                leds[i] = Scroll((i * 256 / 50 + k) % 256);
            else
                leds[i] = CRGB(0, 0, 0);      
        }
        FastLED.show(); 
    }

    // INSTANCE VARIABLES
    Scenes scene;
    CRGB leds[NUM_LEDS];
    // PUT WHATEVER VARIABLES YOU NEED DOWN HERE
    int k = 255;
};

Lights leds;

void setup() {
    delay(3000); // power-up safety delay
    // INITIALIZE LEDS
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(tempLeds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    // CLEAR LEDS
    for (int i = 0; i < NUM_LEDS; i++)
        tempLeds[i] = CRGB(0, 0, 0);

    // INITIALIZE LEDS
    leds.setLEDS(tempLeds);
    FastLED.show();
}

void loop() {
    // --- DO NOT CHANGE THIS ---
    // CHECK DMX INPUT AND SET SCENE
    // TODO: CHECK DMX INPUT FROM BOARD
    int dmxInput = 1;
    leds.setScene(dmxInput);
    leds.displayScene();

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *            PUT FUNCTIONALITY FOR YOUR LIGHTS IMPLEMENTATION BELOW           *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    // PUT WHAT YOU PUT IN THE ENUM HERE
    if(leds.getScene() == RAINBOW) {  //LOOP CODE TO MAKE RAINBOW WORK
        k = k - wheel_speed; // SPEED OF COLOR WHEEL
        leds.setK(k);
        if (k < 0) // RESET COLOR WHEEL
            k = 255;

        // REMOVE LEDs
        decay_check++;
        if (decay_check > decay)
        {
            decay_check = 0;
            if (litLights > 0)
                litLights--;
        }
    }
}