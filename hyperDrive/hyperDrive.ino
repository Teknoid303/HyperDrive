#include "FastLED.h"
#include "pins_arduino.h"


FASTLED_USING_NAMESPACE

// MicroQuad Race Gate
// Starfield Warp Simulation
// using a FastLED Implementation
//
// Dean Nicholson, April 2017

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

// LED strips that randomize the passing of "stars"
#define DATA_PIN_1            6 //D6

#define LED_TYPE            WS2811
#define COLOR_ORDER         GRB

#define NUM_LEDS            147

// Star Parameters
#define LEAD_LEDS            7 // How many LEDs represent the star
#define MAX_STAR_SPEED       5 // max 5?
#define MIN_STAR_SPEED       3 // min 2?
#define STARS_PER_STRAND     3 // Increase for longer strands


CRGB starLeds[NUM_LEDS + LEAD_LEDS + 3]; // Allow for a buffer at the end of the string to avoid congrunet memory overrun

#define INIT_BRIGHTNESS    255
#define FRAMES_PER_SECOND  320
#define FADE_SPEED         40

long randNumber;

// Starfield Variables

uint8_t lastStarPosition[STARS_PER_STRAND];
uint8_t lastStarSpeed[STARS_PER_STRAND];
CRGB    lastStarColor[STARS_PER_STRAND];
uint8_t sHue = 160; // Star color hue - Default to blue
uint8_t sSat = 255;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() {
  int k;
  randomSeed(analogRead(0)); // Randomize from unconnected pin (noise)

  delay(1000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(starLeds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set initial master brightness control
  FastLED.setBrightness(INIT_BRIGHTNESS);

  // Randomize the initial star positions on each line
  for (k = 0; k < STARS_PER_STRAND; k++) {
    lastStarPosition[k] = random8(0, NUM_LEDS - 2);
    lastStarSpeed[k] = random8(MIN_STAR_SPEED, MAX_STAR_SPEED);
  }
}

void loop() {
  starfield();
  int r=0;
  r++;

  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);
  
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
  // send the 'leds' array out to the actual LED strip
  FastLED.show();
}

void starfield() {
  uint8_t j, k, c;
  uint8_t hueValue;

  for (k = 0; k < STARS_PER_STRAND; k++) {
    fadeToBlackBy( starLeds, NUM_LEDS, FADE_SPEED);


    for (j = 0; j < LEAD_LEDS; j++) {
      starLeds[j + lastStarPosition[k]] = lastStarColor[k];
    }

    hueValue = random(0, 255);

    if (lastStarPosition[k] > NUM_LEDS) {
      lastStarPosition[k] = 0;
      lastStarSpeed[k] = random8(MIN_STAR_SPEED, MAX_STAR_SPEED);

      lastStarColor[k] = CHSV(hueValue, sSat, INIT_BRIGHTNESS);
    } else {  
      lastStarPosition[k] = lastStarPosition[k] + lastStarSpeed[k];
    }  
  }
}
