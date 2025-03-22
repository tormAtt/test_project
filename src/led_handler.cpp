#include "led_handler.h"

LED_handler::LED_handler(const uint uart_id_param, const uint baud_rate_param):
    uart_id(uart_id_param), baud_rate(baud_rate_param)
{
    if(uart_id == 0) {
        uart_setup(uart_id, 0, 1, baud_rate);
    } else if(uart_id == 1) {
        uart_setup(uart_id, 4, 5, baud_rate);
        join_lora_network();
    }

    // Initialize read variables
    pos = 0;
    str_received = false;

    // Initialize LED variables and store them in vector
    leds.push_back(LED(20, 500, "LED 1"));
    leds.push_back(LED(21, 500, "LED 2"));
    leds.push_back(LED(22, 500, "LED 3"));
}

void LED_handler::read_handler() {
    // Read UART
    //read_uart();
    int charCount = uart_read(uart_id, (uint8_t *) read_buffer.c_str(), BUFFER_SIZE);

    if(charCount > 0) {
        // String received
        printf("Received: %s\n", read_buffer.c_str());

        // Process string TODO
        if(!read_buffer.empty()) {
            process_command();
        }

        // Reset buffer
        reset_buffer();
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
    join_lora_network();
}

void LED_handler::process_command() {
    // Process command
    // TODO multiple commands simultaneously
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
    str_received = false;
}

void LED_handler::read_uart() {
    int retV = uart_read(uart_id, (uint8_t *) read_buffer.c_str(), read_buffer.size());
    if(retV > 0) {
        read_buffer[retV] = '\0';
        printf("Received: %s\n", read_buffer.c_str());
    }
}

void LED_handler::join_lora_network() {
    std::vector<char *> join_commands;

    // Create commands to join LoRaWAN network
    join_commands.push_back("AT+MODE=LWOTAA\r\n");
    join_commands.push_back("AT+KEY=APPKEY, <appkey>\r\n");
    join_commands.push_back("AT+CLASS=A\r\n");
    join_commands.push_back("AT+PORT=8\r\n");
    join_commands.push_back("AT+JOIN\r\n");

    for(const char *command : join_commands) {
        // Send join command to LoRaWAN network
        printf("Sending command: %s\n", command);
        int retV = 0;

        do {
            uart_send(uart_id, command);
            sleep_ms(500);
            retV = uart_read(uart_id, (uint8_t *) read_buffer.c_str(), BUFFER_SIZE);
        } while(retV == 0);

        if(retV > 0) {
            read_buffer[retV] = '\0';
            printf("Received: %s\n", read_buffer.c_str());
        }
    }
}