#ifndef BUTTONS_H
#define BUTTONS_H

#include <driver/gpio.h>

/**
 * @brief create a push button class
*/
class PushButton {
    private:
        gpio_num_t _pin; /* which gpio is the button connected to? */
        unsigned long _debounceTime; /* debounce time */
        int _lastButtonState = 1; /* previous reading from button input pin */
        int _currentButtonState; /* current reading from button input pin */
        unsigned long long _lastDebounceTime = 0 ;
    

    public:
        PushButton(gpio_num_t);
        void setDebounce(unsigned long);
        bool isPressed();
};

#endif