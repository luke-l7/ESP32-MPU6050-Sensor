#include <Arduino.h>
#include <IMU.hpp>

IMU imu;
float sample_array[7];

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