#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class IMU
{
private:
    Adafruit_MPU6050 mpu_;
    static constexpr mpu6050_accel_range_t A_RANGE = MPU6050_RANGE_8_G;
    static constexpr mpu6050_gyro_range_t G_RANGE = MPU6050_RANGE_500_DEG;
    static constexpr mpu6050_bandwidth_t B_RANGE = MPU6050_BAND_5_HZ;
public:


    IMU(/* args */): mpu_(){};
    ~IMU(){};
    int Begin() noexcept;
};