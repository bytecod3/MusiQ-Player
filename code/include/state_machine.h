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

#define STATE_TIMEOUT 4000 /* time for idle screen to switch back to home screen */

void checkState();
char* getCurrentState(int);

#endif