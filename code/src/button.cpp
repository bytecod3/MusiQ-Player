#include "button.h"
#include <Arduino.h> /* for millis */

/**
 * @brief constructor - create a push button 
*/
PushButton::PushButton(gpio_num_t pin_number) {
    this->_pin = pin_number;
}

/**
 * @brief set debounce time
*/
void PushButton::setDebounce(unsigned long debounce_time) {
    this->_debounceTime = debounce_time;
}

/**
 * @brief check whether the button has been pressed 
*/
bool PushButton::isPressed() {
    /* get the current reading of button */
    int reading = gpio_get_level(this->_pin);

    /**
     * when a pin is pressed, it goes from HIGH to LOW
     * check for switch change
    */
    if (reading != this->_lastButtonState) {
        this->_lastDebounceTime = millis();
    }

    /**
    * check if enough time has passed since last button change
    * if enough time has passed and the state is still the same,
    * then take the current state as the correct state
    */
    if ((millis() - this->_lastDebounceTime) > this->_debounceTime) {
        /* if the butto state has changed */        
        if( reading != this->_currentButtonState) {
            /* update the current button state */
            this->_currentButtonState = reading;

            /* return true if the new buttons state is LOW */
            if (this->_currentButtonState == 0) {
                return true; /* button pressed */
            } else {
                return false;
            }
        }
    }

    /* update the last button state */
    this->_lastButtonState = reading;

}


