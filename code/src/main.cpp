
#include <esp_err.h>
#include <driver/gpio.h>
#include <string.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "defs.h"
#include "bitmaps.h"
#include "button.h"
#include "state_machine.h"
#include "log.h"

/* set DEBUG to 0 to suppress debug messages */
#define DEBUG 1
char message_buffer[20]; /* to hold log messages. Check log.cpp for more details */
/* flags */
int SDCardFoundFlag = 0;

/* sd card info variables */
char SDType[10];
uint64_t SDSize;
char SDSizeBuffer[10];
uint32_t noOfFiles;

/* Function prototypes */
void GPIOInit();
void screenInit();
void bootUp();
void showMenu();
void showHomeScreen();
void SDCardInit();
void SDCardInfo();
void showSDCardInfo();
void SDCardListMusic(fs::FS &fs, const char * dirname);
char* allocateMemory();
void copyFilenameToBuffer(int, char*);


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

const int NUM_MENU_ITEMS = 7;

char menu_items[NUM_MENU_ITEMS][15] = {
    {"Home"},
    {"Music"},
    {"Shuffle"},
    {"Equalizer"},
    {"Settings"},
    {"SD info"},
    {"About"}
};

int selected_menu_item = 0; // item currently selected in the menu
int previous_menu_item; // item before the selected item
int next_menu_item; // item after the selected item

/*===============================================================*
/*===========================FSM variables============================*/
/* state timeout timer */
unsigned long long stateTimeoutCounterCurrent = 0;
unsigned long long stateTimeoutCounterPrevious = 0;

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

/* TODO: assign ISR function pointer to ISRs */

/*=====================================================================*/

void setup() {

    Serial.begin(115200);
    delay(100);

    Serial.println("Serial started...\n");

    /* initialise screen */
    screenInit();

    /* initialize SD card */
    SDCardInit();

    /* get SD card details */
    if(SDCardFoundFlag == 1) {
        SDCardInfo();
    }

    /* dynamically create music list */
    SDCardListMusic(SD, "/");

    #if DEBUG == 1
        if(SDCardFoundFlag == 1) {
            Serial.println("SDCard found");
            SDCardInfo();
            Serial.println(SDType);
            Serial.println(SDSizeBuffer);
        } else {
            Serial.println(message_buffer);
        }

        Serial.println("============MUSIC LIST=============");

        /* list music */
        for (int i = 0; i < noOfFiles; i++) {
            Serial.println(music_list[i]);
        }

    #endif

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
    // #if DEBUG == 1
    //     Serial.print("Current:");Serial.println(getCurrentState(currentState));
    //     Serial.print("Previous:");Serial.println(getCurrentState(previousState));
    // #endif

    switch (currentState) {
        case States::HOME:        
            /* display the homescreen page */
            showHomeScreen();

            break;

        case States::MENU:
            /* display the menu */
            showMenu();
            
            break;

        case States::SD_CARD_INFO:
            /* display SD card details */
            showSDCardInfo();
            break;
        
        default:
            break;
    }

    /*===================================================================*/

    /*===========================PROCESS BUTTON PRESSES FOR DIFFERENT STATES==================*/

   if(  currentState == States::MENU  ) {
        /**
         * MENU STATE
        */
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

        } else if(menuButton.isPressed()) {
            /* process menu choices */
            switch (selected_menu_item){
                /* home choice */
                case 0:
                    currentState = States::HOME;
                    previousState = States::MENU;
                    break;

                /* sd card info */
                case 5:
                    currentState = States::SD_CARD_INFO;
                    previousState = States::MENU;
                
                default:
                    break;
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

        
   } else  if (currentState == States::HOME) {
        /**
         * HOME STATE 
        */
        /* menu button clicked  */
        if(menuButton.isPressed() ) {
            /* state transition */
            currentState = States::MENU;
            previousState = States::HOME;  
        }

       
    } else if (currentState == States::SD_CARD_INFO) {
        /**
         * SD_CARD_INFO state
        */
       if(menuButton.isPressed()) {
            /* state transition */
            /* TODO: implement timeout */
            currentState = States::MENU; // previous state will always be the MENU state
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
 * @brief initialize SD card
*/
void SDCardInit() {
    if(!SD.begin(SD_SLAVE_SELECT)) {
        /* SD card not found. LOG this error */
        system_log(LOG_LEVEL::ERROR, "Insert SD", message_buffer);
        SDCardFoundFlag = 0; /* SD card not found */
    } else {
        /* Otherwise SD card found */
        SDCardFoundFlag = 1;
        
    }
}

/**
 * @brief get info about the SD card
*/
void SDCardInfo() {
    uint8_t SDCardType = SD.cardType();
    
    if (SDCardType == CARD_NONE) {
        /* card not inserted */
        SDCardFoundFlag = 0;
        system_log(LOG_LEVEL::ERROR, "Insert SD", message_buffer);

    } else {
        SDCardFoundFlag = 1;
        /* get type of SD card inserted */
        if(SDCardType == CARD_MMC){
            strcpy(SDType, "MMC");
        } else if(SDCardType == CARD_SD){
            strcpy(SDType, "SD");
        } else if(SDCardType == CARD_SDHC){
            strcpy(SDType, "SDHC");
        } else {
            strcpy(SDType, "UNKNOWN");
        }

        /* get the size of the SD card */
        SDSize = SD.cardSize() / (1024 * 1024 * 1024); /* size in GB */
        sprintf(SDSizeBuffer, "%d GB\n", SDSize ); /* TODO: check size of copied buffer */

        /* no of files is got from the SDCardListMusic Function - that is where we open the SD card and read 
        the names and sizes of individual files */

    }

}

/**
 * @brief show SD card info on screen 
*/
void showSDCardInfo() {
    screen.clearBuffer();
    screen.firstPage();
    do {

        /* set font */
        screen.setFont(u8g2_font_7x13_mf);
        
        screen.drawStr(34, 11, "SD Card Info");
        /* sd type */
        screen.drawStr(1, 25, "TYPE: ");
        screen.drawStr(40, 25, SDType);

        /* sd size */
        screen.drawStr(1, 41, "SIZE: ");
        screen.drawStr(40, 41, SDSizeBuffer);

        /* no of files in system */
        screen.drawStr(1, 59, "FILES: ");
        screen.setCursor(46, 59);
        screen.print(noOfFiles);

    } while( screen.nextPage() );

}

/**
 * @brief dynamically allocate memory to hold mp3 file filename 
*/
char* allocateMemory() {
    char* memAdress = (char*) malloc(FILENAME_LENGTH);
    return memAdress;   
}

/**
 * @brief list music in the SD card
 * All music MUST be on the root of the drive 
 * No music will be read from inner directories
*/
void SDCardListMusic(fs::FS &fs, const char * dirname) {

    if (SDCardFoundFlag == 1) { /* SD card was found */
        File root = fs.open(dirname); /* dirname is passed as / - to list all music in the root */

        if(!root) {
            system_log(LOG_LEVEL::ERROR, "Failed to open dir", message_buffer);
            /* FIXME: return from function?? */
        } 

        /* open files and get their infos */
        File file =  root.openNextFile();

        int j = 0; /* loop index */
        int _no_of_files = 0; /* to store the number of files found in the system */

        while (file) {
            file = root.openNextFile();

            if (!file ) {
                /* no more files */
                break;
            } 

            /* TODO: check for file extension and append only MP3 files to music_list */
            music_list[j] = allocateMemory();

            /* only copy filenames whose length is less than FILENAME_LENGTH */
            if( strlen(file.name()) < FILENAME_LENGTH ) {
                strcpy(music_list[j], file.name());
            }

            j++;    
            _no_of_files++;        

        }

        /* update the number of files */
        noOfFiles = _no_of_files;



    }

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
    screen.clearBuffer(); 
    screen.firstPage();
    do {
        /* selected item background  */
        screen.drawBitmap(0, 22, 128/8, 20, icons_array[icons_array_length - 1]);
        
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

