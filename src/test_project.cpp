#include <iostream>

#include "led_handler.h"

int main()
{
    stdio_init_all();
    printf("Boot\n");

    printf("Creating LED handler\n");
    LED_handler led_handler(0, 115200);
    //LED_handler led_handler(1, 9600);

    while (true) {
        led_handler.read_handler();
        led_handler.blink_leds();
    }
}