#include <Arduino.h>
#include <IMU.hpp>
#include <UART.hpp>

IMU imu;

float sample_array[7];
uint8_t UART_NO = UART_NUM_2;
uint8_t TX_PIN = 16;
uint8_t RX_PIN = 17;
uint8_t RTS_PIN = 4;
uint8_t CTS_PIN = 5;
unsigned int buffer_size = 1024 * 2;
UART uart = UART(UART_NO, buffer_size,TX_PIN, RX_PIN,RTS_PIN,CTS_PIN);


void setup() {
  Serial.begin(9600);
  if (!imu.Begin())
  {
    Serial.println("Unable to find IMU");
    while(1)
    {
      delay(10);
    }
  }
  if(!uart.Open())
  {
    Serial.println("Unable to open UART");
    while(1)
    {
      delay(10);
    }
  }
}

void loop() {
  imu.Sample(sample_array);
  Serial.println("Acceleration X :-");
  Serial.println(sample_array[0]);
  delay(1500);
}