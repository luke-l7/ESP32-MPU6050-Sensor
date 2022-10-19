#include <Arduino.h>
#include <Sensor.hpp>

Sensor IMUSensor;

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
  IMUSensor.start();
}

void loop()
{
  IMUSensor.initiated();
/*   if(IMUSensor.active() && IMUSensor.initiated()){
   IMUSensor.send_sample();
  } */
}