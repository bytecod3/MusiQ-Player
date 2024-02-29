
#include <esp_err.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "defs.h"
#include "menu.h"

/* OLED screen variables */
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128
#define YELLOW_OFFSET 16
#define OLED_SDA 21
#define OLED_SCL 22
U8G2_SSD1306_128X64_NONAME_F_HW_I2C screen(/*R2: rotation 180*/U8G2_R0, /*reset*/U8X8_PIN_NONE, /* clock */ OLED_SCL, /* data */ OLED_SDA);


/* Function prototypes */
void screenInit();
void showSplashScreen();
void showMenu();
void showHomepage();
void cardDetails();


void setup() {

    /* initialise screen */
    screenInit();

}

void loop() {

    showMenu();

}

void screenInit() {
    screen.begin();
    screen.firstPage();
    do {
        screen.setFont(u8g2_font_ncenB14_tr);
        screen.drawStr(0,15,"Hello World!");
    } while ( screen.nextPage() );
}

void showMenu() {
    screen.firstPage();
    do {
        screen.drawBitmap(0, 0, 128/8, 64, menu_page_1);
    } while ( screen.nextPage() );
}