/** @file   led.c
    @authors Azim Rushdi & Xuyang Cai, UC
    @date   15 October 2018
    @brief  Two players ping-pong game

    @defgroup game Simple message display program using tinygl and infrared reader
*/

#include <avr/io.h>
#include "led.h"


/** Turn LED1 on.  */
void led_on (void)
{
    PORTC |= (1 << 2);
}


/** Turn LED1 off.  */
void led_off (void)
{
    PORTC &= ~(1 << 2);
}


/** Initialise LED1.  */
void led_init (void)
{
    DDRC |= (1 << 2);
}
