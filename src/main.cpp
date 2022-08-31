#include <Arduino.h>
#include <IMU.hpp>
#include <UART.hpp>
IMU imu;
float sample_array[7];
uint8_t UART_NO = UART_NUM_2;
uint8_t RX_PIN = 16;
uint8_t TX_PIN = 17;
uint8_t RTS_PIN = UART_PIN_NO_CHANGE;
uint8_t CTS_PIN = 5;


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
}

void loop() {
  imu.Sample(sample_array);
  Serial.println("Acceleration X :-");
  Serial.println(sample_array[0]);
  delay(1500);
}