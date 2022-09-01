#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

class UART
{
private:
    uart_port_t uart_num_;
    QueueHandle_t uart_queue_;
    uint8_t TX_PIN_; 
    uint8_t RX_PIN_;
    uint8_t RTS_PIN_; 
    uint8_t CTS_PIN_; 
    unsigned int buffer_size_ = 1024 * 2;
public:
    UART(uart_port_t uart_num, 
    unsigned int buffer_size,
    uint8_t TX_PIN, 
    uint8_t RX_PIN, 
    uint8_t RTS_PIN, 
    uint8_t CTS_PIN) : uart_num_(uart_num),
                        buffer_size_(buffer_size),
                        TX_PIN_(TX_PIN),
                        RX_PIN_(RX_PIN),
                        RTS_PIN_(RTS_PIN),
                        CTS_PIN_(CTS_PIN){};
    ~UART(){};
    int Open() noexcept;
};
