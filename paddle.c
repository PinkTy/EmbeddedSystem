/** @file   paddle.c
    @authors Azim Rushdi & Xuyang Cai, UC
    @date   15 October 2018
    @brief  module to determine the movement of the paddle

    @defgroup game Simple message display program using tinygl and infrared reader
*/


#include "tinygl.h"
#include "paddle.h"
#include "navswitch.h"
#include "system.h"


/**
    Initialize the paddle position.
*/
void paddle_init(void)
{
    tinygl_draw_line (paddle_top, paddle_bottom, 1);
}


/**
    Determines the movement of paddle.
*/
void move(void)
{
    tinygl_update ();
    navswitch_update ();
    // Moves paddle to the right when user moves the navigation switch to the right
    if(navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        if(paddle_bottom.y < BOTTOM_BOUNDARY) {
            tinygl_draw_line (paddle_top, paddle_bottom, 0);
            paddle_top.y++;
            paddle_bottom.y++;
            tinygl_draw_line (paddle_top, paddle_bottom, 1);
        }
    } else if(navswitch_push_event_p (NAVSWITCH_NORTH)) {
        // Moves paddle to the left when user moves the navigation switch to the left
        if(paddle_top.y > TOP_BOUNDARY) {
            tinygl_draw_line (paddle_top, paddle_bottom, 0);
            paddle_top.y--;
            paddle_bottom.y--;
            tinygl_draw_line (paddle_top, paddle_bottom, 1);
        }
    }
}
