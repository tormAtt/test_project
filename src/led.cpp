#include "led.h"

LED::LED(const uint led_pin_param, const uint delay_param, const char *led_name_param):
    led_pin(led_pin_param), delay(delay_param), led_name(led_name_param), 
    slice_num(pwm_gpio_to_slice_num(led_pin)), channel_num(pwm_gpio_to_channel(led_pin))
{
    // Initialize LED
    printf("Initializing %s\n", led_name);
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize PWM for LED
    cfg = pwm_get_default_config();
    pwm_config_set_wrap(&cfg, max_brihtness - 1);
    pwm_init(slice_num, &cfg, false);
    gpio_set_function(led_pin, GPIO_FUNC_PWM);
    pwm_set_enabled(slice_num, true);

    current_brightness = max_brihtness;
    enabled = true;
}

void LED::enable() {
    printf("%s ENABLED\n", led_name);
    enabled = true;
    led_on();
    // TODO save state to eeprom
}   

void LED::disable() {
    printf("%s DISABLED\n", led_name);
    enabled = false;
    led_off();
    // TODO save state to eeprom
}

void LED::led_toggle() {
    if(!enabled) return;

    printf("%s TOGGLED\n", led_name);
    // Toggle LED
    if(led_state()) led_off(); else led_on();

    sleep_ms(delay);
}

void LED::set_brightness(uint brightness_percentage) {
    if(!enabled) return;
    
    if(brightness_percentage < 0) brightness_percentage = 0;
    else if(brightness_percentage > 100) brightness_percentage = 100;

    // Set brightness
    printf("%s BRIGHTNESS TO %d%%\n", led_name, brightness_percentage);
    pwm_set_chan_level(slice_num, channel_num, (current_brightness = max_brihtness * brightness_percentage / 100) - 1);
    // TODO save state to eeprom
}

const char *LED::led_get_name() {
    return led_name;
}

void LED::led_on() {
    printf("%s TO ON\n", led_name);
    //gpio_put(led_pin, true);
    pwm_set_chan_level(slice_num, channel_num, current_brightness);
    // TODO save state to eeprom
}

void LED::led_off() {
    printf("%s TO OFF\n", led_name);
    //gpio_put(led_pin, false);
    pwm_set_chan_level(slice_num, channel_num, 0);
    // TODO save state to eeprom
}

bool LED::led_state() {
    return gpio_get(led_pin);
}