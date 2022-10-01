#include <stdio.h>
#include <Arduino.h>
#include <atomic>
#include <SensorInternal.hpp>
#include <string.h>
#include <IMU.hpp>>

using namespace SensorInternal;
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
    char command_buffer_[SensorInternal::MAX_LEN_OF_COMMAND]; ///< command buffer of fixed size
    Command final_command_; ///< Stores the final command
    size_t buff_size_; ///< current/final command size
    std::atomic<bool> recieving_; ///< true if the Sensor is recieving a command, false otherwise
    IMU imu_; ///< IMU sensor
    bool active_; ///< indicates whether the sensor is active or not
    bool initiated_; ///< indicates whther the sensor has been initiated (with the init_message_)

    void _transmit(char* buff, size_t size); ///< transmits the sensor data over the UART
    bool _command_available(); ///< returns true if a command has been recieved, false otherwise
    void _listen(); ///< Stores incoming commands till a full one is formed
    void _flush_buffer(); ///< flushes the command buffer
public:
    Sensor();
    ~Sensor(){};
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
     * using the planned mechanism between the master and slave
     * 
     * @note it's a custom mechanism and it can be changed
     * accordingly with the user and the master.
     */
    void send_data();
};


