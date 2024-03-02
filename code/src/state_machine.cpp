#include "state_machine.h"

/**
 * @brief check the current running state and make a transition if 
 * need be
*/
void checkState() {
    return;
}

char* getCurrentState(int state) {
    switch (state) {
    case States::HOME:
        return "HOME";
        break;

    case States::MENU:
        return "MENU";
        break;

    case States::PLAYING:
        return "PLAYING";
        break;

    case States::VOLUME:
        return "VOLUME";
        break;
    
    case States::SD_CARD_INFO:
        return "SD_CARD_INFO";
        break;

    case States::EQ:
        return "EQ";
        break;

    case States::ABOUT:
        return "ABOUT";
        break;
    
    default:
        return "UNDEFINED";
        break;
    }
}