#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <memory>

#include "hardware/uart.h"
#include "led.h"

class LED_handler {
public:
    LED_handler(uint uart_id, uint baud_rate_param);
    // Public functions
    void read_handler();
    void blink_leds();
private:
    // UART variables
    const uint uart_id;
    const uint baud_rate;
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
    void join_lora();
};