#pragma once
#include <iostream>

#include "pico/stdlib.h"

class LED {
public:
    LED(uint led_pin_param, uint delay_param, const char *led_name_param);
    // Public functions
    void enable();
    void disable();
    void led_toggle();
    const char *led_get_name();
private:
    // Member variables
    const uint led_pin;
    const uint delay;
    const char *led_name;
    bool enabled;

    // Private functions
    void led_on();
    void led_off();
    bool led_state();
};