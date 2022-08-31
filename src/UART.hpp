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
    uint8_t RX_PIN;
    uint8_t TX_PIN; 
    uint8_t RTS_PIN; 
    uint8_t CTS_PIN; 
public:
    UART(uart_port_t uart_num) : uart_num_(uart_num){};
    ~UART(){};
    int Open() noexcept;
};
