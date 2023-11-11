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

int max_of_three(int a, int b, int c) {
    if (a >= b && a >= c) {
        return a;
    } else if (b >= a && b >= c) {
        return b;
    } else {
        return c;
    }
}

void initialize_led_task(void* pvParameters) {

	fade_in = false;
	fade_out = false;
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(0);
    while (1)
    {
        if (!data_recived)
        {
        	if (!fade_in)
        	{
				for (int i = 0; i < 200; i += 1)
				{
					FastLED.setBrightness(i);
					fill_solid(leds, NUM_LEDS, CRGB::Aqua);
					FastLED.show();
					vTaskDelay(pdMS_TO_TICKS(12));
				}
				fade_in = true;
        	}
    	}
        else
    	{
        	for (int i = 200; i > 0; i --)
        	     {
        	        FastLED.setBrightness(i);
        	        fill_solid(leds, NUM_LEDS, CRGB::Aqua);
        	        FastLED.show();
        			vTaskDelay(pdMS_TO_TICKS(12));
        	      }
        	fill_solid(leds, NUM_LEDS, CRGB::Black);
        	FastLED.show();
        	fade_out = true;
            vTaskDelete(NULL);
    	}
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 50 milliseconds
    }
}

void flash_led_task(void* pvParameters) {
	bool done = false;
	LED_R = 0;
	LED_G = 0;
	LED_B = 0;
	while (1)
	{
		FastLED.setBrightness(255);
		if(LED_R != led_states[0] || LED_G != led_states[1] || LED_B != led_states[2])
		{
			done = 0;
		}
		else
		{
			done = 1;
		}
		if (fade_out && !done)
		{
			for (int i = 0; i < 255; i++)
			{
				if (LED_R < led_states[0])
				{
					LED_R++;
				}
				else if (LED_R > led_states[0])
				{
					LED_R--;
				}
				if (LED_G < led_states[1])
				{
					LED_G++;
				}
				else if (LED_G > led_states[1])
				{
					LED_G--;
				}
				if (LED_B < led_states[2])
				{
					LED_B++;
				}
				else if (LED_G > led_states[2])
				{
					LED_B--;
				}
				for (int i = 0; i < 7; i++)
				{
					leds[i] = CRGB(LED_R, LED_G, LED_B);
				}
				FastLED.show();
				vTaskDelay(pdMS_TO_TICKS(12));
			}
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
