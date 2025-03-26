#pragma once
#include <iostream>

#include "pico/stdlib.h"
#include "hardware/pwm.h"

class LED {
public:
    LED(uint led_pin_param, uint delay_param, const char *led_name_param);
    // Public functions
    void enable();
    void disable();
    void led_toggle();
    void set_brightness(uint brightness_percentage);
    const char *led_get_name();
private:
    // LED variables
    const uint led_pin;
    const uint delay;
    const char *led_name;
    bool enabled;
    bool is_led_on;

    // PWM variables
    const uint slice_num;
    const uint channel_num;
    pwm_config cfg;
    const uint max_brihtness = 1000;
    uint current_brightness;

    // Private functions
    void led_on();
    void led_off();
};