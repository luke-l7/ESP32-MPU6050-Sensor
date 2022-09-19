#include <Arduino.h>
#include <IMU.hpp>

IMU imu;

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
  Serial2.begin(115200);
/*   if (!imu.Begin())
  {
    Serial.println("Unable to find IMU");
    while(1)
    {
      delay(10);
    }
  } */
  pinMode(2, OUTPUT);
}
int count = 0;
void loop()
{
  char s = '5';
  if(Serial2.write(&s,1) > 0)
  {
    count++;
  }
  else{
    Serial.println(count);
  }
}