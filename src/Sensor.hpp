#ifndef SENSOR_HEADER
#define SENSOR_HEADER
#include <stdio.h>
#include <Arduino.h>
#include <atomic>
#include <SensorInternal.hpp>
#include <string.h>
#include <IMU.hpp>

using SensorInternal::Command;
/**
 * Sensor Simulator class 
 */
class Sensor
{
private:
    size_t missed_;
    const char start_letter_ = '$'; ///> Command starting letter
    const char end_letter_ = '#'; ///> Command ending letter
    const Command ping_command_{"0001", 4}; ///> Sensor ping command
    const Command ping_response_ = {"11", 2}; ///> Sensor ping response
    const Command init_message_ = {"00051", 5}; ///> Sensor initialization message

    // Pay attention that the GYRO_ULTIPLIER_ and ACCELERATION_MULTIPLIER_ 
    // are two component examples to the agreed upon as the communication interface between the 
    // slave and the master, thus ther is no specific reason for it other than the agreed upon rules
    float GYRO_MULTIPLIER_ = 2000; ///> Gyro data multiplier (before transmission)
    float ACCELERATION_MULTIPLIER_ = 25600; ///> Acceleration multiplier (before transmission)
    char command_buffer_[SensorInternal::MAX_LEN_OF_COMMAND]; ///< command buffer of fixed size
    float sample_buffer_[8]; ///< IMU sample buffer
    Command final_command_; ///< Stores the final command
    size_t buff_size_; ///< current/final command size
    std::atomic<bool> recieving_; ///< true if the Sensor is recieving a command, false otherwise
    IMU imu_{}; ///< IMU sensor
    bool active_; ///< indicates whether the sensor is active or not
    std::atomic<bool> initiated_; ///< indicates whther the sensor has been initiated (with the init_message_)

    void _transmit_over_serial(const char* buff, size_t size) const noexcept; ///> transmits the sensor data over the UART
    bool _command_available(); ///> returns true if a command has been recieved, false otherwise
    void _listen(); ///> Stores incoming commands till a full one is formed
    void _flush_buffer(); ///> flushes the command buffer
    void _ping_back(); ///> Upon recieving the ping command, this function pings the response
public:
    Sensor(): buff_size_(0), recieving_(false), initiated_(false){};
    ~Sensor(){};
    /**
     * Starts the sensor's tools 
     */
    void start() noexcept;
    /**
     * Returns true if the Sensor is active
     */
    bool active() noexcept;
    /**
     * Waits for ping command from Master 
     * If successfull, the LED connectected
     * to GPIO 2 will start flashing
     * 
     * @note a reset is needed for the microcontroller to
     * turn off the flashing
     */
    bool initiated() noexcept;
    /**
     * Sends the sampled data over the UART
     * using the agreed upon mechanism between the master and slave
     * 
     * @note If the Sensor hasn´t been initiated yet
     * then this function will have no effect.
     * 
     * @note Since it's a custom mechanism, it can be 
     * changed accordingly with what the user requires.
     */
    void send_sample();
};
#endif


