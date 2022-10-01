#include <Sensor.hpp>


void flash() ///< used for debugging
{
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
}

Sensor::Sensor(): buff_size_(0), recieving_(false)
{
    Serial2.begin(115200);
    if (!imu_.Begin())
    {
        Serial.println("Unable to find IMU");
        return;
    }
    active_ = true;
}

void Sensor::_listen()
{
    char inChar;
    if (Serial2.available()) ///< Read next char
    {
        inChar = Serial2.read();
        Serial.println(inChar);
    }
    else 
        return;

    if (inChar == start_letter_ ) ///< start recieving
    {
        recieving_.exchange(true);
        buff_size_ = 0;
        return;
    }
    if (inChar == end_letter_) ///< end transmission
    {
        recieving_.exchange(false); ///< end of recieving
        final_command_.assign(command_buffer_, buff_size_);
    }    

    if (recieving_.load()) ///< if recieving command
    {
        if (buff_size_ >= MAX_LEN_OF_COMMAND)
        {
            buff_size_ = 0; ///< overwrite the current command
        }
        command_buffer_[buff_size_++] = inChar;
        return;
    }
}

bool Sensor::active() noexcept
{
    return active_;
}

bool Sensor::initiated() noexcept
{
    _listen();
    if (final_command_.available())
    {
        return final_command_.is_identical(ping_command_);
    }
}

void Sensor::send_data()
{
    
}
