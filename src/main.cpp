#include <Arduino.h>
#include <IMU.hpp>
#include <Sensor.hpp>

void flashThrice()
{
  for (size_t i = 0; i < 3; i++)
  {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}
int count = 0;
Sensor s;
void loop()
{
  if(s.initiated()){
   s.send_data();
  }
}