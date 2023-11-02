#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "FastLED.h"
#include "FX.h"

#include "app_main.h"
#include "FastLED.h"
#include "driver/gpio.h"

#define LED_PIN    21  // GPIO pin connected to the LED strip
#define NUM_LEDS   7 // Number of LEDs in your strip

CRGB leds[NUM_LEDS];

void led_task(void* pvParameters) {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(128);

    while (1) {
        // Set all LEDs to red
        fill_solid(leds, NUM_LEDS, CRGB::Red);
        FastLED.show();

        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds

        // Turn off all LEDs (set to black)
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();

        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds
    }
}

void app_mainn() {
    xTaskCreate(led_task, "LED Task", 4096, NULL, 5, NULL);
}