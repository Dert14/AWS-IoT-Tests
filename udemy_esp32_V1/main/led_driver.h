/*
 * app_main.h
 *
 *  Created on: 2 lis 2023
 *      Author: marci
 */


#ifndef MAIN_LED_DRIVER_H_
#define MAIN_LED_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

void flash_led(); // Declare a C linkage function
void init_led();
_Bool fade_in;
_Bool fade_out;
int LED_R;
int LED_G;
int LED_B;
#ifdef __cplusplus
}
#endif

#endif /* MAIN_LED_DRIVER_H_ */
