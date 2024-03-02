
#ifndef DEFS_H
#define DEFS_H

#include <driver/gpio.h>

/* FSM states */
enum States{
    HOME = 0,
    MENU,
    PLAYING,
    VOLUME_CHANGE,
    SD_CARD_INFO,
    EQ,
    ABOUT

};

#define TIMEOUT 4000 /* time for idle screen to switch back to home screen */

#define DEBOUNCE_TIME 20

/* push button input pins */
#define UP_BUTTON_PIN GPIO_NUM_34
#define DOWN_BUTTON_PIN GPIO_NUM_35
#define MENU_BUTTON_PIN GPIO_NUM_33
#define LEFT_BUTTON_PIN GPIO_NUM_32
#define RIGHT_BUTTON_PIN GPIO_NUM_25



#endif