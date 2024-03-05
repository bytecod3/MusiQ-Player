#include <U8g2lib.h>

/*==================OLED screen variables===================== */
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128
#define YELLOW_OFFSET 16
#define OLED_SDA 21
#define OLED_SCL 22
U8G2_SSD1306_128X64_NONAME_F_HW_I2C screen(/*R2: rotation 180*/U8G2_R0, /*reset*/U8X8_PIN_NONE, /* clock */ OLED_SCL, /* data */ OLED_SDA);

void setup() {

  screen.begin();
  screen.setColorIndex(1);

}

void loop() {
  screen.firstPage(); 
  do {

    screen.drawCircle(64, 32, 3); // inner circle
    screen.drawDisc(64, 32, 6, U8G2_DRAW_UPPER_RIGHT);

  } while (screen.nextPage() );
}
