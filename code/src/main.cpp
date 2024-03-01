
#include <esp_err.h>
#include <driver/gpio.h>
// #include <esp32-hal-misc.c>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "defs.h"
#include "bitmaps.h"
#include "button.h"

int time = millis();

/* Function prototypes */
void GPIOInit();
void screenInit();
void showSplashScreen();
void showMenu();
void showHomepage();
void SDcardDetails();


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

void setup() {

    /* initialise screen */
    screenInit();

}

void loop() {

    /* update menu items  */
    previous_menu_item = selected_menu_item - 1;
    if (previous_menu_item < 0) {
        previous_menu_item = NUM_MENU_ITEMS - 1;
    }

    next_menu_item = selected_menu_item + 1;
    if (next_menu_item > NUM_MENU_ITEMS) {
        next_menu_item = 0;
    }

    showMenu();

}

/**
 * @brief initialise GPIO
*/
void GPIOInit() {
    for (int i = 0; i < 5; i++ ) {
        gpio_set_direction(control_buttons[i], GPIO_MODE_INPUT);
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