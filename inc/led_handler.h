#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <memory>

//#include "hardware/uart.h"
#include "led.h"

extern "C" {
    #include "uart.h"
}

#define BUFFER_SIZE 80

class LED_handler {
public:
    LED_handler(uint uart_id_param, uint baud_rate_param);
    // Public functions
    void read_handler();
    void blink_leds();
private:
    // UART variables
    const uint baud_rate;
    const uint uart_id;
    uart_inst_t *uart;

    // LED variables
    std::vector<LED> leds;

    // Read variables
    std::string read_buffer;
    uint pos;
    bool str_received;

    // Private functions
    void initialize_uart0();
    void initialize_uart1();
    void process_command();
    void reset_buffer();
    void read_uart();
    void join_lora_network();
};