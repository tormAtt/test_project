#include "led_handler.h"

LED_handler::LED_handler(const uint uart_id, const uint baud_rate_param):
    baud_rate(baud_rate_param)
{
    // Initialize UART
    if(uart_id == 0)
    // cmsis-dap debugger
        initialize_uart0();
    else if(uart_id == 1)
    // LORA module
        initialize_uart1();
    else
        printf("Invalid UART ID %i\n", uart_id);

    pos = 0;

    // Populate vector with LED objects
    leds.push_back(LED(20, 500, "LED 1"));
    leds.push_back(LED(21, 500, "LED 2"));
    leds.push_back(LED(22, 500, "LED 3"));
}

void LED_handler::read_uart() {
    // Read UART
    while(uart_is_readable(uart)) {
        char c = uart_getc(uart);
        if(c == '\n' || c == '\r') {
            read_buffer += c;

            // String received
            printf("Received: %s\n", read_buffer.c_str());

            // Process string TODO
            if(!read_buffer.empty()) {
                process_command();
            }

            // Reset buffer
            reset_buffer();
        } else {
            // Append character to buffer
            read_buffer += c;
        }
    }
}

void LED_handler::blink_leds() {
    // Blink LEDs
    for(LED& led : leds) led.led_toggle();
}

void LED_handler::initialize_uart0() {
    // Initialize UART0
    uart = uart0;
    uart_init(uart, baud_rate);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
}

void LED_handler::initialize_uart1() {
    // Initialize UART1
    uart = uart1;
    uart_init(uart, baud_rate);
    gpio_set_function(4, GPIO_FUNC_UART);
    gpio_set_function(5, GPIO_FUNC_UART);
}

void LED_handler::process_command() {
    // Process command
    for(LED& led : leds) {
        if(read_buffer.find(led.led_get_name()) != std::string::npos) {
            if(read_buffer.find("ENABLE") != std::string::npos) {
                led.enable();
            } else if(read_buffer.find("DISABLE") != std::string::npos) {
                led.disable();
            }
            break;
        }
    }
}

void LED_handler::reset_buffer() {
    // Reset buffer
    read_buffer = std::string();
    pos = 0;
}