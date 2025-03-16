#pragma once
#include <vector>
#include <string>
#include <memory>

#include "hardware/uart.h"
#include "led.h"

class LED_handler {
public:
    LED_handler(uint uart_id, uint baud_rate_param);
    // Public functions
    void read_uart();
    void blink_leds();
private:
    // Member variables
    const uint uart_id;
    const uint baud_rate;
    uart_inst_t *uart;
    std::vector<LED> leds;
    std::string read_buffer;
    uint pos;

    // Private functions
    void initialize_uart0();
    void initialize_uart1();
    void process_command();
    void reset_buffer();
    void uart_read_debugger();
    void uart_read_lora();
};