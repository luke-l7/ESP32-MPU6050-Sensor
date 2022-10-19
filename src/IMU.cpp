#include <IMU.hpp>

int IMU::Begin() noexcept
{
    if (!mpu_.begin()) 
    {
        return 0;
    }
    mpu_.setAccelerometerRange(A_RANGE);
    mpu_.setGyroRange(G_RANGE);
    mpu_.setFilterBandwidth(B_RANGE);
    return 1;
}

void IMU::Sample(float sample_buff[8]) noexcept
{
    sensors_event_t a, g, temp;
    mpu_.getEvent(&a, &g, &temp);
    sample_buff[0] = g.gyro.x;
    sample_buff[1] = g.gyro.y;
    sample_buff[2] = g.gyro.z;
    sample_buff[3] = temp.temperature;
    sample_buff[4] = a.acceleration.x;
    sample_buff[5] = a.acceleration.y;
    sample_buff[6] = a.acceleration.z;
    sample_buff[7] = temp.temperature;
}