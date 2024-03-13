#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H 


/* FSM states */
enum States{
    BOOTUP,
    HOME,
    MENU,
    SELECTING_MUSIC,
    PLAYING,
    SHUFFLING,
    VOLUME,
    SD_CARD_INFO,
    EQ,
    SETTINGS,
    SHUFFLE_MENU,
    ABOUT
};

#define STATE_TIMEOUT 4000 /* time before switching to previous screen due to inactivity */

void checkState();
char* getCurrentState(int);

#endif