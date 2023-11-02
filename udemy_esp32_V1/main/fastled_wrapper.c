/*
 * fastled_wrapper.c
 *
 *  Created on: 2 lis 2023
 *      Author: marci
 */
#include "fastled_wrapper.h"

CRGB leds[NUM_LEDS];

void init_leds() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(128);
}

void set_leds_red() {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
}

