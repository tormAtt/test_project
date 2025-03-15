#include "led.h"

LED::LED(const uint led_pin_param, const uint delay_param, const char *led_name_param):
    led_pin(led_pin_param), delay(delay_param), led_name(led_name_param)
{
    // Initialize LED
    printf("Initializing %s\n", led_name);
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    enabled = true;
}

void LED::enable() {
    printf("%s ENABLED\n", led_name);
    enabled = true;
    led_on();
}   

void LED::disable() {
    printf("%s DISABLED\n", led_name);
    enabled = false;
    led_off();
}

void LED::led_toggle() {
    if(!enabled) return;

    printf("%s TOGGLED\n", led_name);
    // Toggle LED
    if(led_state()) led_off(); else led_on();

    sleep_ms(delay);
}

const char *LED::led_get_name() {
    return led_name;
}

void LED::led_on() {
    printf("%s TO ON\n", led_name);
    gpio_put(led_pin, true);
}

void LED::led_off() {
    printf("%s TO OFF\n", led_name);
    gpio_put(led_pin, false);
}

bool LED::led_state() {
    return gpio_get(led_pin);
}