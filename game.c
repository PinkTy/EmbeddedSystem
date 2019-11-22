/** @file   game.c
    @authors Azim Rushdi & Xuyang Cai, UC
    @date   15 October 2018
    @brief  Two players ping-pong game

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
#include "pio.h"

#define PACER_RATE 1000
#define MESSAGE_RATE 25

// Initialize BUZZER port
#define PIEZO1_PIO PIO_DEFINE (PORT_D, 4)
#define PIEZO2_PIO PIO_DEFINE (PORT_D, 6)
#define TONE_FREQUENCY1 440
#define LOOP_RATE (TONE_FREQUENCY * 2)

// Declare ball position
tinygl_point_t ball = {3, 3};

// Declare paddle top and bottom position
tinygl_point_t paddle_top = {4, 2};
tinygl_point_t paddle_bottom = {4, 4};

// Declare the win text
char* win_text = "YOU WIN";

// Start_flag value is 0 before the game starts
// and becomes 1 after the game starts
static int start_flag = 0;


/**
    if ucfk recieve the win message, it will dispaly the "you win" text
    else it will recieve the position of ball.
    @param paddle_top: the top of paddle
    @param paddle_bottom: the bottom of paddle
*/
void ready_recieve(tinygl_point_t paddle_top, tinygl_point_t paddle_bottom)
{
    if (ir_uart_read_ready_p ()) {
        char recieve_buffer;
        recieve_buffer = ir_uart_getc();
        // 'w' represents the win message
        if(recieve_buffer == 'w') {
            tinygl_draw_line (paddle_top, paddle_bottom, 0);
            tinygl_draw_point (ball, 0);
            tinygl_text (win_text);
            while(1) {
                pacer_wait();
                tinygl_update();
                // If player win the game, player will recieve the sound
                pio_output_toggle(PIEZO1_PIO);
                pio_output_toggle(PIEZO2_PIO);
            }
        } else {
            // The game already start
            start_flag = 1;
            ball_change(recieve_buffer);

        }
    }
}

/**
    initialize the buzzer
*/
void buzzer_init(void)
{
    pio_config_set(PIEZO1_PIO, PIO_OUTPUT_LOW);
    pio_config_set(PIEZO2_PIO, PIO_OUTPUT_HIGH);
}


/**
    Initialize the game, include system, paddle, ball, display, etc.
*/
void game_init(void)
{
    system_init();
    buzzer_init();
    tinygl_init (PACER_RATE);
    paddle_init();
    ball_init();
    led_init();
    navswitch_init ();
    pacer_init (PACER_RATE);
    ir_uart_init ();
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
}



/**
    main function of whole game.
*/
int main (void)
{
    // Initialize the ball task
    uint8_t ball_tick = 0;
    game_init();

    while (1) {
        tinygl_update();
        pacer_wait();
        ready_recieve(paddle_top, paddle_bottom);
        move();

        // If player press navswitch, the game will start, and set the start_flag to 1
        if(navswitch_push_event_p (NAVSWITCH_PUSH)) {
            start_flag = 1;
        }
        // Player can choose their own paddle's position before starting the game
        if(start_flag == 0) {
            before_game_start(paddle_top);
        } else {
            tinygl_draw_point (ball, 1);
            // Ball task
            if(ball_tick >= 200) {
                ball_tick = 0;
                game_start(paddle_top, paddle_bottom);
            }
            ball_tick++;
        }

    }
}
