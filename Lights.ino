#include "FastLED.h"
#include "Rainbow/Rainbow.h"
//LED LIGHTING SETUP
#define LED_PIN = 6
#define NUM_LEDS = 500
#define BRIGHTNESS = 50
#define LED_TYPE = "WS2811"
#define COLOR_ORDER = "GRB"

// SCENES ENUMERATED TYPE
enum Scenes {
    RAINBOW = 0,
    // PUT THE SCENES YOU DEVELOP BELOW
};

// LIGHTS CLASS
class Lights {

public:
    // DEFAULT: INITIALIZE LIGHTS TO BLACK
    Lights() { 
        for (int i = 0; i < NUM_LEDS; i++)
            leds[i] = CRGB(0, 0, 0);
    }
    // TAKES IN LEDS TO ASSIGN LEDS TO
    Lights(CRGB leds_in[NUM_LEDS]) : leds(leds_in) {}

    // GETTER AND SETTER FOR SCENES
    void setScene(Scenes s) { scene = s; }
    Scenes getScene() { return scene; }
    // SETS THE LEDS TO THE INPUT
    void setLEDS(CRGB leds_in[NUM_LEDS]) {
        for(int i = NUM_LEDS - 1; i >= 0; --i) {
            led[i] = leds_in[i];
        }
    }

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              PUT METHODS FOR YOUR LIGHTS IMPLEMENTATION BELOW               *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    // INSTANCE VARIABLES
    Scenes scene;
    CRGB leds[NUM_LEDS];
};

// --- DO NOT CHANGE THIS ---
CRGB tempLeds[NUM_LEDS];
int scene;

// --- PUT SPECIFIC VARIABLES YOU NEED BELOW ---
// RAINBOW WAVE SETTINGS
int wheel_speed = 3;
int k = 255; // COLOR WHEEL POSITION
int decay = 10000; // HOW MANY MS BEFORE ONE LIGHT DECAY
int decay_check = 0;
long pre_react = 0; // NEW SPIKE CONVERSION
long litLights = 500; // NUMBER OF LEDs BEING LIT
long post_react = 0; // OLD SPIKE CONVERSION

Lights leds;
// --- ADD YOUR OBJECTS BELOW ---
RainbowScene rainbowObj;

// RUNS ONCE ON STARTUP
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
    // INITIALIZE RAINBOW OBJECT
    rainbowObj.setLEDS(tempLeds)
    FastLED.show();
}

// CONTINUOUSLY RUNS IMMEDIATELY AFTER SETUP
void loop() {
    // --- DO NOT CHANGE THIS ---
    // CHECK DMX INPUT AND SET SCENE
    // TODO: CHECK DMX INPUT FROM BOARD
    int dmxInput = 0;
    leds.setScene(dmxInput);
    leds.displayScene();

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *            PUT FUNCTIONALITY FOR YOUR LIGHTS IMPLEMENTATION BELOW           *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    // PUT WHAT YOU PUT IN THE ENUM HERE
    if(leds.getScene() == RAINBOW) {  //LOOP CODE TO MAKE RAINBOW WORK
        // BEGIN RAINBOW
        rainbowObj.rainbow()
        k = k - wheel_speed; // SPEED OF COLOR WHEEL
        rainbowObj.setK(k);
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