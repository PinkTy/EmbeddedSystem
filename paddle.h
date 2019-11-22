/** @file   paddle.h
    @authors Azim Rushdi & Xuyang Cai, UC
    @date   15 October 2018
    @brief  Determines the movement of paddle

    @defgroup game Simple message display program using tinygl and infrared reader
*/

#ifndef PADDLE_H
#define PADDLE_H
#define TOP_BOUNDARY 0
#define BOTTOM_BOUNDARY 6

extern tinygl_point_t paddle_top;
extern tinygl_point_t paddle_bottom;

/**
    Initialise the position of the paddle.
*/
void paddle_init(void);

/**
    Determines the movement of paddle.
*/
void move(void);


#endif
