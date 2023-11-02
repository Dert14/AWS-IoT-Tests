/*
 * fastleds.cpp
 *
 *  Created on: 2 lis 2023
 *      Author: marci
 */
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <FastLED.h>

#define LED_PIN    21  // GPIO pin connected to the LED strip
#define NUM_LEDS   7 // Number of LEDs in your strip

CRGB leds[NUM_LEDS];

void led_task(void *pvParameters) {
    // Initialize FastLED
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(128); // Set LED brightness (0-255)

    while (1) {
        // Set all LEDs to red
        fill_solid(leds, NUM_LEDS, CRGB::Red);
        FastLED.show();

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

void app_mainn() {
    xTaskCreate(led_task, "LED Task", 4096, NULL, 5, NULL);
}
