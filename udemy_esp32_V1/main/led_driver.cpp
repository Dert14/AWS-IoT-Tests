#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "FastLED.h"
#include "FX.h"

#include "FastLED.h"
#include "driver/gpio.h"
#include "aws_connection.h"

#include "led_driver.h"

#define LED_PIN    21  // GPIO pin connected to the LED strip
#define NUM_LEDS   7 // Number of LEDs in your strip

CRGB leds[NUM_LEDS];

typedef struct {
    int param1;
    float param2;
    // Add more parameters as needed
} TaskParameters;

void initialize_led_task(void* pvParameters) {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(200);
    while (1) {
        if (data_recived) {
        	//fill_solid(leds, NUM_LEDS, CRGB::Green);
        	//FastLED.show();
        	vTaskDelete(NULL);
    	}
        else
    	{
            fill_solid(leds, NUM_LEDS, CRGB::White);
            FastLED.show();
    	}
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 milliseconds
    }
}

void flash_led_task(void* pvParameters) {
	while (1)
	{
		if (data_recived)
		{
			fill_solid(leds, NUM_LEDS, CRGB::Green);
			FastLED.show();
		}
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void init_led() {
    xTaskCreate(initialize_led_task, "init LED Task", 4096, NULL, 5, NULL);
}

void flash_led() {
    xTaskCreate(flash_led_task, "start LED Task", 4096, NULL, 4, NULL);
}