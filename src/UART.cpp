#include <UART.hpp>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

int UART::Open() noexcept
{
    uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
    .rx_flow_ctrl_thresh = 122,
    };
    // Configure UART parameters
    int config = uart_param_config(uart_num_, &uart_config);
    int set = uart_set_pin(uart_num_, TX_PIN_, RX_PIN_, RTS_PIN_, CTS_PIN_);
    int install = uart_driver_install(uart_num_, buffer_size_, \
                                        buffer_size_, 10, &uart_queue_, 0);
    return config|set|install;
}