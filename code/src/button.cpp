#include "button.h"
#include <Arduino.h> /* for millis */

/**
 * @brief constructor - create a push button 
*/
PushButton::PushButton(gpio_num_t pin_number) {
    /* set button as input */
    this->_pin = pin_number;
    gpio_set_direction(this->_pin, GPIO_MODE_INPUT);

    this->_lastButtonState = 1;
    this->_lastDebounceTime = 0;
    
}

/**
 * @brief get buttons last state - for debugging
*/
int PushButton::getLastState() {
    return this->_lastButtonState;
}

/**
 * @brief get buttons current state - for debugging
*/
int PushButton::getCurrentState() {
    return this->_currentButtonState;
}

/**
 * @brief set debounce time
*/
void PushButton::setDebounce(unsigned long debounce_time) {
    this->_debounceTime = debounce_time;
}

/**
 * @brief check if button is pressed
*/
bool PushButton::isPressed() {
    if ((this->_currentButtonState == 1) && (this->_lastButtonState == 0)) {
        return true; /* button is pressed */
    } else {
        return false; /* not pressed */
    }
}

/**
 * @brief check whether the button has been pressed 
*/
void PushButton::loop() {
    /* get the current reading of button */
    int reading = gpio_get_level(this->_pin);
    unsigned long long currentTime = millis();

    /**
     * if the button changed, due to noise or pressing
    */
    if (reading != this->_lastButtonState) {
        /* reset the debouncing timer */
        this->_lastDebounceTime = currentTime;
    }

    /**
    * check if enough time has passed since last button change
    * if enough time has passed and the state is still the same,
    * then take the current state as the correct state
    */
    if ((currentTime - this->_lastDebounceTime) > this->_debounceTime) {
        /* if the button state has changed */        
        
        // if (reading != this->_currentButtonState) {
            
        // }
        this->_currentButtonState = reading;

    }

    /* update the last button state */
    this->_lastButtonState = reading;

}


