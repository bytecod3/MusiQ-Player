#include <Preferences.h>

Preferences user_settings;

typedef struct {
  uint8_t auto_sleep;   /* if set to off, write a 0 here, else can be set to 5 min or 10 min */
  uint8_t shuffle;      /* on or off */
  uint8_t sort_files;   /* can be on or off. If on, arrange files from SD card alphabetically, if off, show files as ordered in the SD card */ 
  
} Settings;


/*
 * @brief update NVS if the user changes the device settings 
 * @param Settings* object containing the values of the settings fields
 */
void updateSettings(Settings* setting) {
  setting->auto_sleep = 5;
  setting->shuffle = 1;
  setting->sort_files = 0;  
}

void setup() {
  Serial.begin(115200);
  /* create a settings object */
  Settings mySettings;
  Settings* ptr_settings; /* ptr to settings type */

  ptr_settings = &mySettings;  
  
  user_settings.begin("settings", false); /* creates a preferences namespace named 'settings' with R/W permissions */

  /* create dummy settings */
  updateSettings(ptr_settings);

  uint8_t auto_sleep = user_settings.getUInt("auto_sleep", 0); /* default values 0*/
  uint8_t shuffle = user_settings.getUInt("shuffle", 0);
  uint8_t sort_files = user_settings.getUInt("sort_files", 0);  

  Serial.printf("Current auto-sleep value: %u\n", auto_sleep);
  Serial.printf("Current shuffle value: %u\n", shuffle);
  Serial.printf("Current sort-files value: %u\n", sort_files);

  user_settings.putUInt("auto_sleep", ptr_settings->auto_sleep);
  user_settings.putUInt("shuffle", ptr_settings->shuffle);
  user_settings.putUInt("sort_files", ptr_settings->sort_files);
  

  user_settings.end();
   
}

void loop() {
  

}
