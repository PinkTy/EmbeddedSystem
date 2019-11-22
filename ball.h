/** @file   ball.h
    @authors Azim Rushdi & Xuyang Cai, UC
    @date   15 October 2018
    @brief  Determines the position of ping-pong ball

    @defgroup game Simple message display program using tinygl and infrared reader
*/

#ifndef BALL_H
#define BALL_H
#define DISPLAY_PACER 1000
#define LEFT 10
#define RIGHT 20
#define PADDLE_BOTTOM_BOUNDARY 4
#define PADDLE_TOP_BOUNDARY -1
#define RIGHT_BOUNDARY 0
#define LEFT_BOUNDARY 6
#define RIGHT_CORNER -1
#define LEFT_CORNER 7

extern tinygl_point_t ball;


/**
    Intialise ping-pong ball.
*/
void ball_init(void);

/**
    Initialise ping-pong ball position.
*/
void before_game_start(tinygl_point_t paddle_top);

/**
    Determines direction of the ball & transmit signal to the other UCFK4 board.
*/
void game_start(tinygl_point_t paddle_top, tinygl_point_t paddle_bottom);

/**
    Receive innfrared signal from the other UCFK4 board.
*/
void ball_change(char recieve_buffer);

#endif
