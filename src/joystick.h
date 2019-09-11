#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "adc.h"
#include <avr/io.h>

#define JOY_X_CH ADC_CH1
#define JOY_Y_CH ADC_CH2
#define JOY_BTN PB3

#define THRESHOLD_UP 90
#define THRESHOLD_DOWN 10
#define THRESHOLD_LEFT 10
#define THRESHOLD_RIGHT 90

typedef struct pos {
    int x;
    int y;
} pos_t;

typedef enum joy_btn_dir {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
} joy_btn_dir_t;

void joystick_init();
pos_t joystick_read_x_and_y_raw();
pos_t joystick_get_position();
int joystick_read_btn();
joy_btn_dir_t joystick_get_direction();

void joystick_test();


#endif // JOYSTICK_h