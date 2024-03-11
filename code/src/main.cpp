
#include <esp_err.h>
#include <driver/gpio.h>
#include <string.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <stdlib.h>
#include <Preferences.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "defs.h"
#include "bitmaps.h"
#include "button.h"
#include "state_machine.h"
#include "log.h"

/* Function prototypes */
void GPIOInit();
void screenInit();
void bootUp();
void cycleThroughMenu(uint8_t);
void showMenu();
void showHomeScreen();
void showPlayingScreen();
void showSettingsMenu();
void SDCardInit();
void SDCardInfo();
void showSDCardInfo();
void SDCardListMusic(fs::FS &fs, const char * dirname);
char* allocateMemory();
void copyFilenameToBuffer(int, char*);
void showMusicFiles();
void updateSettings(Settings*);
void showShuffleOptions();

/* set DEBUG to 0 to suppress debug messages */
#define DEBUG 1
char message_buffer[20]; /* to hold log messages. Check log.cpp for more details */

/* flags */
int SDCardFoundFlag = 0;

/* NVS variables - to store configuration */
Preferences user_settings;
Settings mySettings;
Settings* ptr_settings = &mySettings;

/* sd card info variables */
char SDType[10];
uint64_t SDSize;
char SDSizeBuffer[10];
uint32_t noOfFiles;

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

/**
 * Device menus
*/
const int NUM_MENU_ITEMS = 7;
const int NUM_SETTINGS_MENU_ITEMS = 4;
const int NUM_SHUFFLE_MENU_ITEMS = 3;
const int NUM_AUTO_SLEEP_MENU_ITEMS = 5;

char menu_items[NUM_MENU_ITEMS][15] = {
    {"Home"},
    {"Music"},
    {"Shuffle"},
    {"Equalizer"},
    {"Settings"},
    {"SD info"},
    {"About"}
};

char setting_menu_items[NUM_SETTINGS_MENU_ITEMS][15] = {
    {"Shuffle"},
    {"Auto sleep"},
    {"Sort files"},
    {"Back"}
};

char shuffle_menu_options[NUM_SHUFFLE_MENU_ITEMS][15] = {
    {"On"},
    {"Off"},
    {"Back"}
};

char auto_sleep_options[NUM_AUTO_SLEEP_MENU_ITEMS][15] = {
    {"Off"},
    {"5 Min"},
    {"10 Min"},
    {"30 Min"},
    {"Back"}
};

/* For cycling through lists of items */
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
    #if DEBUG == 1
        // Serial.print("Current:");Serial.println(getCurrentState(currentState));
        // Serial.print("Previous:");Serial.println(getCurrentState(previousState));
    #endif

    switch (currentState) {
        case States::HOME:        
            /* display the homescreen page */
            showHomeScreen();

            break;

        case States::MENU:
            /* display the menu */
            showMenu();
            
            break;

        case States::SELECTING_MUSIC:
            /* list all the MP3 music in the SD card */
            showMusicFiles();
            break;

        case States::PLAYING:
            /* play the selected track and show the playing screen */
            showPlayingScreen();
            break;
        
        case States::SETTINGS:
            /* show settings menu */
            showSettingsMenu();
            break;

        case States::SHUFFLE_MENU:
            /* shuffle options - on or off */
            showShuffleOptions();
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
            /* move one menu item up */
            selected_menu_item = selected_menu_item - 1;
            if (selected_menu_item < 0) {
                selected_menu_item = NUM_MENU_ITEMS - 1;
            }

        } else if(downButton.isPressed()) {
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

                /* music choice */
                case 1:
                    currentState = States::SELECTING_MUSIC;
                    previousState = States::MENU;
                    break;

                /* settings choice */
                case 4:
                    currentState = States::SETTINGS;
                    previousState = States::MENU;
                    break;

                /* sd card info */
                case 5:
                    currentState = States::SD_CARD_INFO;
                    previousState = States::MENU;
                    break;
                
                default:
                    break;

            }

        }
        
    /*===========================End of MENU state==========================================*/
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

    /*================================end of HOME state===================================*/
    } else if (currentState == States::SELECTING_MUSIC) {
        /**
         * SELECTING_MUSIC STATE   
        */
       /* cycle through music files */
        if(upButton.isPressed()) {
            /* move one menu item up */
            selected_menu_item = selected_menu_item - 1;
            if (selected_menu_item < 0) {
                selected_menu_item = noOfFiles - 1;
            }

        } else if(downButton.isPressed()) {
            /* move one menu item up */
            selected_menu_item = selected_menu_item + 1;
            if (selected_menu_item >= noOfFiles) {
                selected_menu_item = 0;
            } 

        }else if(menuButton.isPressed()) {
            /*  a song is selected, go to playing mode and start playing the selected song */
            /* state transition */
            currentState = States::PLAYING;
            //previousState = States::SELECTING_MUSIC;

       }

    /*=======================end of SELECTING_MUSIC state================================*/
    } else if (currentState == States::PLAYING) {
        if(menuButton.isPressed()) {
            /* pause playing track */
            currentState = States::MENU;

        } else if(upButton.isPressed()) {
            /*TODO: increase volume */
        } else if(downButton.isPressed()) {
            /* TODO: derease volume */
        }
        
    /*=======================end of PLAYING state================================*/
    } else if (currentState == States::SETTINGS) {
        /**
         * SETTINGS state
        */
       /* cycle through menu items */
        if(upButton.isPressed()) {
            /* move one menu item up */
            selected_menu_item = selected_menu_item - 1;
            if (selected_menu_item < 0) {
                selected_menu_item = NUM_SETTINGS_MENU_ITEMS - 1;
            }

        } else if(downButton.isPressed()) {
            /* move one menu item up */
            selected_menu_item = selected_menu_item + 1;
            if (selected_menu_item >= NUM_SETTINGS_MENU_ITEMS) {
                selected_menu_item = 0;
            } 
        }
         else if(menuButton.isPressed()) {
            /* state transition */
            /* show settings options */
            Serial.println(setting_menu_items[selected_menu_item]);

            switch (selected_menu_item) {

            case 0:
                /* Shuffle on */
                currentState = States::SHUFFLE_MENU;
                break;
            
            /* shuffle off */
            case 1:
                break;

            /* auto sleep */
            case 2:
                /* set auto sleep time */
                break;
            
            /* sort files */
            case 3:
                break;

            /* back to main menu */
            case 4:
                currentState = States::MENU;
                break;
            
            default:
                break;
            }
       }

    //    /*=========================end of SETTINGS state ==============================*/


    } else if (currentState == States::SD_CARD_INFO) {
        /**
         * SD_CARD_INFO state
        */
       if(menuButton.isPressed()) {
            /* state transition */
            /* TODO: implement timeout */
            currentState = States::MENU; // previous state will always be the MENU state
       }

    /*==========================end of SD_CARD_INFO state==============================*/
    } else if (currentState == States::SHUFFLE_MENU) {
        /**
         * SHUFFLE_MENU state
        */

       if(upButton.isPressed()) {
            /* previous option  */
            selected_menu_item = selected_menu_item - 1;
            if (selected_menu_item < 0) {
                selected_menu_item = NUM_SETTINGS_MENU_ITEMS - 1;
            }

       } else if(downButton.isPressed()) {
            /* next option */
            selected_menu_item = selected_menu_item + 1;
            if (selected_menu_item >= NUM_SETTINGS_MENU_ITEMS) {
                selected_menu_item = 0;
            } 

       } else if (menuButton.isPressed()) {
            /* save selected option to NVS. If selected item is back, go back to SETTINGS MENU */

            switch (selected_menu_item) {
                case 0:
                    /* shuffle on */
                    updateSettings(ptr_settings);
                    break;

                case 1:
                    /* shuffle off */
                    Serial.println("Shuffle off");
                    break;

                case 2:
                    /* back to settings menu */
                    currentState = States::SETTINGS;
                    break;
                
                default:
                    break;
                }
       }


    }
    
    /* get the menu next and previous items */
    cycleThroughMenu(currentState);
}

/**
* @brief update menu items
* perform check on the no. of menu items for the current state because main menu and settings menu have different 
* no. of menu items 
*/
void cycleThroughMenu(uint8_t state){

    previous_menu_item = selected_menu_item - 1;
    
    if(state == States::MENU) {
        /* process menu for MENU state*/
        if (previous_menu_item < 0) {
            previous_menu_item = NUM_MENU_ITEMS - 1;
        } 
    } else if (currentState == States::SETTINGS) {
        /* process menu for SETTINGS state*/
        if (previous_menu_item < 0) {
            previous_menu_item = NUM_SETTINGS_MENU_ITEMS - 1;
        } 
    } else if (state == States::SELECTING_MUSIC) {
        /* process menu for selecting music */
        if (previous_menu_item < 0) {
            previous_menu_item = noOfFiles - 1;
        } 
    } else if (state == States::SHUFFLE_MENU) {

        /* process menu for selecting shuffle on or off */
        if(previous_menu_item < 0) {
            previous_menu_item = NUM_SHUFFLE_MENU_ITEMS - 1;
        }

    }

    next_menu_item = selected_menu_item + 1;
    if(currentState == States::MENU) {
        if (next_menu_item >= NUM_MENU_ITEMS) {
            next_menu_item = 0;
        }
    } else if( currentState == States::SETTINGS ) {
        if (next_menu_item >= NUM_SETTINGS_MENU_ITEMS) {
            next_menu_item = 0;
        }
    } else if (currentState == States::SELECTING_MUSIC) {
        if (next_menu_item >= noOfFiles) {
            next_menu_item = 0;
        }
    } else if (currentState == States::SHUFFLE_MENU) {
        if (next_menu_item >= NUM_SHUFFLE_MENU_ITEMS) {
            next_menu_item = 0;
        }
    }

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
 * @brief list music files on the screen 
*/
void showMusicFiles() {

    screen.firstPage();
    do {

        /* selected item background  */
        screen.drawBitmap(0, 22, 128/8, 20, icons_array[icons_array_length - 1]);

        // previous item
        screen.setFont(u8g2_font_8x13_mf);
        screen.drawBitmap(1, 2, 16/8, 16, icons_array[music_icon_index]); 
        screen.drawStr(23, 16, music_list[previous_menu_item]);

        // selected item
        screen.setFont(u8g2_font_8x13B_mf);
        screen.drawBitmap(1, 23, 16/8, 16, icons_array[music_icon_index]); 
        screen.drawStr(23, 38, music_list[selected_menu_item]);

        // next item
        screen.setFont(u8g2_font_8x13_mf);
        screen.drawBitmap(1, 46, 16/8, 16, icons_array[music_icon_index]); 
        screen.drawStr(23, 60, music_list[next_menu_item]);

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
 * @brief show settings menu
*/
void showSettingsMenu() {

    screen.firstPage();
    do {
        /* selected item background  */
        screen.drawBitmap(0, 22, 128/8, 20, icons_array[icons_array_length - 1]);

        screen.setFont(u8g2_font_9x15_mf);
        screen.drawBitmap(1, 2, 16/8, 16, icons_array[previous_menu_item]); 
        screen.drawStr(23, 16, setting_menu_items[previous_menu_item]);

        screen.setFont(u8g2_font_9x15B_mf);
        screen.drawBitmap(1, 23, 16/8, 16, icons_array[selected_menu_item]); 
        screen.drawStr(23, 38, setting_menu_items[selected_menu_item]);

        screen.setFont(u8g2_font_9x15_mf);
        screen.drawBitmap(1, 46, 16/8, 16, icons_array[next_menu_item]); 
        screen.drawStr(23, 60, setting_menu_items[next_menu_item]);

    } while (screen.nextPage() );
}

/**
 * @brief show shuffle settings options 
*/
void showShuffleOptions() {
    screen.firstPage();
    do {
        /* selected item background  */
        screen.drawBitmap(0, 22, 128/8, 20, icons_array[icons_array_length - 1]);

        screen.setFont(u8g2_font_9x15_mf);
        screen.drawBitmap(1, 2, 16/8, 16, icons_array[previous_menu_item]); 
        screen.drawStr(23, 16, shuffle_menu_options[previous_menu_item]);

        screen.setFont(u8g2_font_9x15B_mf);
        screen.drawBitmap(1, 23, 16/8, 16, icons_array[selected_menu_item]); 
        screen.drawStr(23, 38, shuffle_menu_options[selected_menu_item]);

        screen.setFont(u8g2_font_9x15_mf);
        screen.drawBitmap(1, 46, 16/8, 16, icons_array[next_menu_item]); 
        screen.drawStr(23, 60, shuffle_menu_options[next_menu_item]);


    } while (screen.nextPage());

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
 * @brief display playing screen animation
*/
void showPlayingScreen() {

    screen.firstPage();
    do {
        /* battery icon */
        /* TODO: make this dynamic with battery */
        screen.drawBitmap(2, 2, 16/8, 16, icons_array[10]);
        screen.setFont(u8g2_font_8x13_mf);
        screen.drawStr(20, 15, "10%");

        /* music file index - show at the top right of screen */
        screen.setCursor(SCREEN_WIDTH - 5, 15);
        screen.print(selected_menu_item); /* the selected menu item is the file number - previous state is SELECTING_MUSIC */

        /* eq lines left and right */
        screen.drawLine(0,SCREEN_HEIGHT/2, SCREEN_WIDTH/2 - OUTER_DISC_RADIUS, SCREEN_HEIGHT/2);
        screen.drawLine(SCREEN_WIDTH/2+OUTER_DISC_RADIUS, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

        /* 1st quarter */
        int i = random(0, 4); /* for varying the y start point- make the animation more realisitic */
        screen.drawVLine(2, 28-i, 4-i); 
        screen.drawVLine(4, 24-i, 16-i);
        screen.drawVLine(6, 20-i, 24-i);
        screen.drawVLine(8, 16-i, 32-i); 
        screen.drawVLine(10, 12-i, 40-i); 

        /* 2nd quarter */
        screen.drawVLine(12, 16-i, 32-i);
        screen.drawVLine(14, 20-i, 24-i);
        screen.drawVLine(16, 24-i, 16-i);
        screen.drawVLine(18, 28-i, 8-i); 

        /* 3rd quarter */
        screen.drawVLine(24, 28-i, 8-i); 
        screen.drawVLine(26, 24-i, 16-i);
        screen.drawVLine(28, 20-i, 24-i);
        screen.drawVLine(30, 16-i, 32-i); 
        screen.drawVLine(32, 12-i, 40-i); 

        /* 4th quarter */
        screen.drawVLine(34, 12-i, 40-i);
        screen.drawVLine(36, 16-i, 32-i);
        screen.drawVLine(38, 20-i, 24-i); 
        screen.drawVLine(40, 24-i, 16-i);
        screen.drawVLine(42, 28-i, 8-i);

        /* two circular discs */
        screen.drawCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, INNER_DISC_RADIUS);
        screen.drawCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, OUTER_DISC_RADIUS);
        screen.setFont(u8g2_font_8x13_mf);
        screen.drawStr(5, SCREEN_HEIGHT-1, music_list[selected_menu_item]);

        /* 5th quarter ? */
        screen.drawVLine(88, 28-i, 8-i); 
        screen.drawVLine(90, 24-i, 16-i);
        screen.drawVLine(92, 20-i, 24-i);
        screen.drawVLine(94, 16-i, 32-i); 
        screen.drawVLine(96, 12-i, 40-i); 

        /* 6th quarter */
        screen.drawVLine(98, 12-i, 40-i);
        screen.drawVLine(100, 16-i, 32-i);
        screen.drawVLine(102, 20-i, 24-i);
        screen.drawVLine(104, 24-i, 16-i);
        screen.drawVLine(106, 28-i, 8-i); 

        /* 7th quarter */
        screen.drawVLine(110, 28-i, 8-i); 
        screen.drawVLine(112, 24-i, 16-i);
        screen.drawVLine(114, 20-i, 24-i);
        screen.drawVLine(116, 16-i, 32-i); 
        screen.drawVLine(118, 12-i, 40-i); 

        /* 8th quarter */
        screen.drawVLine(120, 16-i, 32-i);
        screen.drawVLine(122, 20-i, 24-i); 
        screen.drawVLine(124, 24-i, 16-i);
        screen.drawVLine(126, 28-i, 8-i);
        
    } while (screen.nextPage() );
    
}


/**
 *@brief update NVS if the user changes the device settings 
 *@param Settings* object containing the values of the settings fields

 */
void updateSettings(Settings* setting) {

    /* read the current values from user namespace */
    
  setting->auto_sleep = 0;
  setting->shuffle = 0;
  setting->sort_files = 0;  
}