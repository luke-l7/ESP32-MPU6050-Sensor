#include <stdio.h>

class Sensor
{
private:
    size_t missed_;
public:
    Sensor(/* args */);
    ~Sensor();
    /*Trasmit bytes given the UART in IMU style*/
    void Trasmit();
};

Sensor::Sensor(/* args */)
{
}


Sensor::~Sensor()
{
}
