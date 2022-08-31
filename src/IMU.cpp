#include <IMU.hpp>

int IMU::Begin() noexcept
{
    if (!mpu_.begin()) 
    {
        return 1;
    }
    mpu_.setAccelerometerRange(A_RANGE);
    mpu_.setGyroRange(G_RANGE);
    mpu_.setFilterBandwidth(B_RANGE);
    return 0;
}

void IMU::Sample(float sample_buff[7]) noexcept
{
    sensors_event_t a, g, temp;
    mpu_.getEvent(&a, &g, &temp);
    sample_buff[0] = a.acceleration.x;
    sample_buff[1] = a.acceleration.y;
    sample_buff[2] = a.acceleration.z;
    sample_buff[3] = g.gyro.x;
    sample_buff[4] = g.gyro.y;
    sample_buff[5] = g.gyro.z;
    sample_buff[6] = temp.temperature;
}