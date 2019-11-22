/** @file   led.h
    @authors Azim Rushdi & Xuyang Cai, UC
    @date   15 October 2018
    @brief  Switches LED ON and OFF

    @defgroup game Simple message display program using tinygl and infrared reader
*/

#ifndef LED_H
#define LED_H

/**
    Turn LED1 on.
*/
void led_on (void);


/**
    Turn LED1 off.
*/
void led_off (void);


/**
    Initialise LED1.
*/
void led_init (void);
#endif
