#include <Sensor.hpp>
using namespace SensorInternal;
void flash() ///< used for debugging
{
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
}

void Sensor::start() noexcept
{
    Serial2.begin(625000);
    if (!imu_.Begin())
    {
        Serial.println("Unable to find IMU");
        return;
    }
    active_ = true;
}

void Sensor::_ping_back()
{
    const char* response = ping_response_.getCommand();
    _transmit_over_serial(response, strlen(response));
}

void Sensor::_transmit_over_serial(const char* buff, size_t size) const noexcept
{
    Serial.print("transmitting response...");
    Serial2.write(PREFIX); ///> Start transmission
    size_t bytes = Serial2.write(buff, size);
    Serial.write(bytes);
    Serial2.write(SUFFIX); ///> End transmission
    Serial2.flush(true);
}

void Sensor::_listen()
{
    char inChar;
    if (Serial2.available()) ///< Read next char
    {
        inChar = Serial2.read();
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
        Serial.println(command_buffer_);
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
    // todo : add realtion adctive param
    if(initiated_)
        return true;

    _listen();
    // if final command is available and not recieving, as to not interrupt the recieving proccess
    if (final_command_.available() && (!recieving_.load()))
    {
        if(final_command_.is_identical(ping_command_))
        {
            _ping_back();
            final_command_.reset();
        }
        if (final_command_.is_identical(init_message_))
        {
            Serial.print("2");
            initiated_.exchange(true);
        }
    }
    return initiated_;
}

void Sensor::send_sample()
{
    if (!initiated_)
        return;
    
    imu_.Sample(sample_buffer_);
    for(const auto axis_sample : sample_buffer_)
    {
        const char* buff = reinterpret_cast<const char *>(axis_sample);
        _transmit_over_serial(buff, sizeof(float));
    }
}
