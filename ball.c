/** @file   ball.c
    @authors Azim Rushdi & Xuyang Cai, UC
    @date   15 October 2018
    @brief  Module to determine the position of the ball

    @defgroup game Simple message display program using tinygl and infrared reader
*/


#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font3x5_1.h"
#include "paddle.h"
#include "ball.h"
#include "led.h"


// Message displayed when a player lose
char* lost_text = "YOU LOST";

// Row increment variable
static int rowinc = 1;

// Column increment variable
static int colinc = 1;


/**
    initialize the ball position.
*/
void ball_init(void)
{
    tinygl_draw_point (ball, 0);
}


/**
    before game start, this function will use the top position of paddle to set ball position.
    @param paddle_top: the top position of the paddle
*/
void before_game_start(tinygl_point_t paddle_top)
{
    ball.y = paddle_top.y + 1;
}


/**
    this function defines the direction movement of ball.
    @param paddle_top: the top position of the paddle
    @param paddle_bottom: the bottom position of the paddle
*/
void game_start(tinygl_point_t paddle_top, tinygl_point_t paddle_bottom)
{
    // Sets the previous ball invisible
    tinygl_draw_point (ball, 0);
    ball.x -= colinc;
    ball.y -= rowinc;

    // If the ball hits paddle, the direction of ball changes
    if(ball.x == PADDLE_BOTTOM_BOUNDARY && ((ball.y <= paddle_bottom.y && ball.y >= paddle_top.y) || (ball.y == RIGHT_CORNER && (paddle_top.y == 0 || paddle_top.y ==1))
                                            || (ball.y == LEFT_CORNER && (paddle_bottom.y == 5 || paddle_bottom.y == 1)))) {
        // Ball moves to the left if it hits the right corner and the paddle catches it
        if(ball.y == RIGHT_CORNER) {

            rowinc = -1;
            // Sets the ball position
            ball.x = 3;
            ball.y = 0;
            // Ball moves to the right if it hits the left corner and the paddle catches it
        } else if(ball.y == LEFT_CORNER) {
            rowinc = 1;
            // Sets the ball position
            ball.x = 3;
            ball.y = 6;
        } else {
            ball.x += colinc * 2;
        }
        // If paddle recieve the ball, the blue LED will flash
        led_on();
        pacer_wait();
        led_off();
        colinc = 1;
        // If the player miss the ball, game over and display the "YOU LOST" message
    } else if(ball.x == PADDLE_BOTTOM_BOUNDARY && (ball.y > paddle_bottom.y || ball.y < paddle_top.y)) {
        tinygl_draw_line (paddle_top, paddle_bottom, 0);
        tinygl_draw_point (ball, 0);
        tinygl_text (lost_text);
        // Send the win message to other ucfk
        char send_buffer;
        send_buffer = 'w';
        ir_uart_putc (send_buffer);
        pacer_init (DISPLAY_PACER);
        while(1) {
            pacer_wait();
            tinygl_update();
        }
    } else {
        // If the ball hit the left or right boundary, the direction of ball changes
        if (ball.y > LEFT_BOUNDARY || ball.y < RIGHT_BOUNDARY) {
            ball.y += rowinc * 2;
            rowinc = -rowinc;
        }
    }
    tinygl_draw_point (ball, 1);

    // Send the ball position message to other ucfk
    if(ball.x == PADDLE_TOP_BOUNDARY) {
        tinygl_draw_point (ball, 0);
        char send_buffer;
        // The message of ball positon
        send_buffer = -(ball.y - 6);
        // The message of ball direction
        if(rowinc == 1) {
            send_buffer += RIGHT;
        } else {
            send_buffer += LEFT;
        }
        ir_uart_putc (send_buffer);
    }
}


/**
    if the ucfk recieve the ball message, this function will declare the position of ball
    @param recieve_buffer: the recieve character
*/
void ball_change(char recieve_buffer)
{
    ball.x = 0;
    colinc = -1;

    // If the direction of the ball is left, declare the direction
    if(recieve_buffer >= LEFT && recieve_buffer < RIGHT) {
        ball.y = recieve_buffer - LEFT;
        rowinc = 1;
        // If the direction of the ball is right, declare the direction
    } else {
        ball.y = recieve_buffer - RIGHT;
        rowinc = -1;
    }
}
