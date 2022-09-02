#include <UART.hpp>
#include <Arduino.h>
#include <math.h>
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
/*     Serial.println("config :-");
    Serial.println(config);
    Serial.println("set pins:-");
    Serial.println(set);
    Serial.println("driver install :-");
    Serial.println(install); */

    return !(config|set|install);
}

int UART::Transmit(char* buff, size_t size)
{
    return uart_tx_chars(uart_num_, buff, size);
}

int UART::Receive(char* buff, size_t size)
{
    size_t length = 0;
    uart_get_buffered_data_len(uart_num_, &length);
    length = min<size_t>(length, size);
    return uart_read_bytes(uart_num_, buff, length, 100);
}
/**
 * @brief Removes the data on the RX buffer
 * 
 */
void UART::Flush()
{
    uart_flush(uart_num_);
}

