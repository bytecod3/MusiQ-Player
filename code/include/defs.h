
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
#define RIGHT_BUTTON_PIN GPIO_NUM_25  /*TODO: Use pin 23 for the final code on PCB - 25 is being used by the internal DAC */

/* slave select pin for SD card */
#define SD_SLAVE_SELECT GPIO_NUM_5

#define MAX_NO_OF_FILES 200 // max number of file in the SD - get this from the no of files from SD card
#define FILENAME_LENGTH 25 // file name length including '.mp3' extension

/* to hold mp3 filenames */
char* music_list[MAX_NO_OF_FILES];

/* playing screen animation variables */
#define OUTER_DISC_RADIUS 15
#define INNER_DISC_RADIUS 3
#define EQ_ANIMATION_SPACING 2
#define OFFSET 16
int l = (128/2-OUTER_DISC_RADIUS)/4;
int h = 16;

/* typdef for settings variables */
typedef struct _userSettings {
    uint8_t auto_sleep;   /* if set to off, write a 0 here, else can be set to 5 min or 10 min */
    uint8_t shuffle;      /* on or off */
    uint8_t sort_files;   /* can be on or off. If on, arrange files from SD card alphabetically, if off, show files as ordered in the SD card */ 
  
} Settings;

#endif
