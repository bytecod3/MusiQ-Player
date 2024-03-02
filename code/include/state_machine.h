#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H 


/* FSM states */
enum States{
    HOME = 0,
    MENU,
    PLAYING,
    VOLUME,
    SD_CARD_INFO,
    EQ,
    ABOUT
};

#define STATE_TIMEOUT 4000 /* time before switching to previous screen due to inactivity */

void checkState();
char* getCurrentState(int);

#endif