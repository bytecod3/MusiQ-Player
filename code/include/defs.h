
#ifndef DEFS_H
#define DEFS_H

#include <driver/gpio.h>

/* FSM states */
enum States{
    HOMEPAGE = 0,
    MENU,
    PLAYING,
    VOLUME_CHANGE,
    CARD_INFO

};

/* push button input pins */
#define UP_BUTTON GPIO_NUM_34
#define DOWN_BUTTON GPIO_NUM_35
#define MENU_BUTTON GPIO_NUM_36
#define LEFT_BUTTON GPIO_NUM_37
#define RIGHT_BUTTON GPIO_NUM_38

const gpio_num_t control_buttons[5] = {
    UP_BUTTON,
    DOWN_BUTTON,
    MENU_BUTTON,
    LEFT_BUTTON,
    RIGHT_BUTTON
};


#endif