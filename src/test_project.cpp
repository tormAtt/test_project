#include <iostream>

#include "led_handler.h"

int main()
{
    stdio_init_all();
    printf("Boot\n");

    printf("Creating LED handler\n");
    LED_handler led_handler(0, 115200);

    while (true) {
        led_handler.read_uart();
        led_handler.blink_leds();
    }
}