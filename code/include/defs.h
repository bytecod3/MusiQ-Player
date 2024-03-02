
#ifndef DEFS_H
#define DEFS_H

#include <driver/gpio.h>

#define DEBOUNCE_TIME 20
#define BOOTUP_TIMEOUT 3000 // show logo time in milliseconds

/* push button input pins */
#define UP_BUTTON_PIN GPIO_NUM_34
#define DOWN_BUTTON_PIN GPIO_NUM_35
#define MENU_BUTTON_PIN GPIO_NUM_33
#define LEFT_BUTTON_PIN GPIO_NUM_32
#define RIGHT_BUTTON_PIN GPIO_NUM_25

#endif