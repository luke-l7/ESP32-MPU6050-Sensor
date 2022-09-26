#include <stdio.h>
/**
 * Sensor Simulator class 
 */
class Sensor
{
private:
    size_t missed_;
    const char start_letter_ = '$'; ///> Command starting letter
    const char end_letter_ = '#'; ///> Command ending letter
    const char* ping_command_ = "0001"; ///> Sensor ping command
    const char* ping_response_ = "11"; ///> Sensor ping response
    const char* init_message_ = "00051"; ///> Sensor initialization message
    void transmit(char* buff, size_t size);
    void recieve(char* buff, size_t size);
public:
    Sensor(/* args */){};
    ~Sensor(){};
    void active();
};


