
#include <esp_err.h>
#include <driver/gpio.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "defs.h"
#include "bitmaps.h"
#include "button.h"
#include "state_machine.h"

/* set DEBUG to 0 to suppress debug messages */
#define DEBUG 1

/* Function prototypes */
void GPIOInit();
void screenInit();
void bootUp();
void showMenu();
void showHomeScreen();
void SDcardDetails();

/* ISRs */


/*===========================Buttons===========================*/
PushButton upButton(UP_BUTTON_PIN);
PushButton downButton(DOWN_BUTTON_PIN);
PushButton menuButton(MENU_BUTTON_PIN);
PushButton leftButton(LEFT_BUTTON_PIN);
PushButton rightButton(RIGHT_BUTTON_PIN);

/*=============================================================*/


/*==================OLED screen variables===================== */
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128
#define YELLOW_OFFSET 16
#define OLED_SDA 21
#define OLED_SCL 22
U8G2_SSD1306_128X64_NONAME_F_HW_I2C screen(/*R2: rotation 180*/U8G2_R0, /*reset*/U8X8_PIN_NONE, /* clock */ OLED_SCL, /* data */ OLED_SDA);

const int NUM_MENU_ITEMS = 6;

char menu_items[NUM_MENU_ITEMS][15] = {
    {"Home"},
    {"Music"},
    {"Shuffle"},
    {"Equalizer"},
    {"Settings"},
    {"About"}
};

int selected_menu_item = 0; // item currently selected in the menu
int previous_menu_item; // item before the selected item
int next_menu_item; // item after the selected item

/*===============================================================*/

/*===========================FSM variables============================*/
/* state timeout timer */
unsigned long long stateTimeoutCounter = 0;

/* starting state */
int currentState = States::HOME;
int previousState = States::HOME; /* at start, the current state and previous state are the same */

static void menuButtonISR(void* arg);
static void upButtonISR(void* arg);
static void downButtonISR(void* arg);
static void leftButtonISR(void* arg);
static void rightButtonISR(void* arg);

/* pointers to ISRs */
static void (*ptrMenuButtonISR)(void * );
static void (*ptrUpButtonISR) (void *);
static void (*ptrDownButtonISR) (void *);
static void (*ptrLeftButtonISR) (void *);
static void (*ptrRightButtonISR) (void *);

/* assign ISR function pointer to ISRs */



/*=====================================================================*/


void setup() {

    Serial.begin(115200);
    delay(100);

    Serial.println("Serial started...\n");

    /* initialise screen */
    screenInit();

    /* set debounce times for buttons */
    upButton.setDebounce(DEBOUNCE_TIME);
    downButton.setDebounce(DEBOUNCE_TIME);
    menuButton.setDebounce(DEBOUNCE_TIME);
    leftButton.setDebounce(DEBOUNCE_TIME);
    rightButton.setDebounce(DEBOUNCE_TIME);

    /* display bootup screen */
    // while( (millis() - stateTimeoutCounter) < BOOTUP_TIMEOUT ) {
    //     bootUp();
    // }
    
}


void loop() {

    /* loop function for buttons */
    upButton.loop();
    downButton.loop();
    menuButton.loop();
    leftButton.loop();
    rightButton.loop();

    // Serial.print("UP current state: "); Serial.println(upButton.getCurrentState());

    /*=====================FINITE STATE MACHINE=========================*/
    #if DEBUG == 1
        Serial.println(getCurrentState(currentState));
    #endif

    switch (currentState) {
    case States::HOME:
        /* menu button clicked  */
        if(menuButton.isPressed() ) {
            /* state transition */
            currentState = States::MENU;
            previousState = States::HOME;

        }
        
        /* display the homescreen page */
        showHomeScreen();

        break;

    case States::MENU:
        /* start timeout countdown */
        stateTimeoutCounter = millis();
        showMenu();

        break;
    
    default:
        break;
    }

    /*===================================================================*/

    /*===========================PROCESS BUTTON PRESSES==================*/
    
    if (currentState == States::MENU) {
        /* cycle through menu items */
        if(upButton.isPressed()) {
            Serial.println("up button pressed");
            /* move one menu item up */
            selected_menu_item = selected_menu_item - 1;
            if (selected_menu_item < 0) {
                selected_menu_item = NUM_MENU_ITEMS - 1;
            }

        } else if(downButton.isPressed()) {
            Serial.println("down button pressed");
            /* move one menu item up */
            selected_menu_item = selected_menu_item + 1;
            if (selected_menu_item >= NUM_MENU_ITEMS) {
                selected_menu_item = 0;
            }
        }

        /* update menu items  */
        previous_menu_item = selected_menu_item - 1;
        if (previous_menu_item < 0) {
            previous_menu_item = NUM_MENU_ITEMS - 1;
        }

        next_menu_item = selected_menu_item + 1;
        if (next_menu_item >= NUM_MENU_ITEMS) {
            next_menu_item = 0;
        }

    }

    /*==================================================================*/


}

/**
 * @brief display bootup screen 
*/
void bootUp() {
    screen.firstPage();
    do {
        screen.drawStr(10, 25, "MuSiQ v1.0"); // TODO: add logo
    } while ( screen.nextPage() );
}

/**
 * @brief Initialize oled screen
 * @param none
*/
void screenInit() {
    screen.begin();
    
    screen.setColorIndex(1);
   
}

/**
 * @brief Display menu on screen
 * @param none
*/
void showMenu() {

    // check for timeout
    if( millis() - stateTimeoutCounter >= STATE_TIMEOUT ) {
        // check the previous state 
        if(currentState == States::MENU && previousState == States::HOME) {
            /* go back home */
            currentState = States::HOME;
            previousState = States::MENU;            
        }
        
    }

    screen.firstPage();
    do {
        // selected item background
        screen.drawBitmap(0, 22, 128/8, 20, icons_array[9]);
        
        // previous item
        screen.setFont(u8g2_font_9x15_mf);
        screen.drawBitmap(1, 2, 16/8, 16, icons_array[previous_menu_item]); 
        screen.drawStr(23, 16, menu_items[previous_menu_item]);

        // selected item
        screen.setFont(u8g2_font_9x15B_mf);
        screen.drawBitmap(1, 23, 16/8, 16, icons_array[selected_menu_item]); 
        screen.drawStr(23, 38, menu_items[selected_menu_item]);

        // next item
        screen.setFont(u8g2_font_9x15_mf);
        screen.drawBitmap(1, 46, 16/8, 16, icons_array[next_menu_item]); 
        screen.drawStr(23, 60, menu_items[next_menu_item]);

        
    } while ( screen.nextPage() );

}

/**
 * @brief Show home screen
*/
void showHomeScreen() {
    screen.firstPage() ;
    do {
        screen.drawBitmap(0,0, 128/8, 64, home_screen);
    } while (screen.nextPage() );
}

/**
 * @brief get the next state
*/

/**
 * ============================= ISRs===============================
*/

// static void menuButtonISR(void* arg) {
//     /* change state to MENU */
//     state = States::MENU;
// }

// static void upButtonISR(void* arg) {
//     /* change state to MENU */
//     state = States::MENU;
// }

// static void downButtonISR(void* arg) {
//     /* chage state to MENU */
//     state = States::MENU;
// }

// static void leftButtonISR(void* arg) {
//     /* chage state to MENU */
//     state = States::MENU;
// }

// static void rightButtonISR(void* arg) {
//     /* chage state to MENU */
//     state = States::MENU;
// }


/*==================================================================*/
