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