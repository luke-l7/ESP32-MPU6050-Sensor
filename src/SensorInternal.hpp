#ifndef SENSOR_INTERNAL_
#define SENSOR_INTERNAL_



#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <numeric>
#include <type_traits>



namespace SensorInternal{

    const static size_t MAX_LEN_OF_COMMAND = 10; ///< Max length of a command
    const static size_t LEN_OF_SAMPLE = 7;
    const static uint8_t PREFIX = '$'; ///> Start of transimission symbol
    const static uint8_t SUFFIX = '#'; ///> End of transmission symbol
    
    // #pragma pack(push,1)
    // typedef struct PingCommand{
    //     std::array<byte, 4> params = {'0','0','0','1'};
    // }PingCommand;
    // #pragma pack(pop)
    // static_assert(4 == sizeof(PingCommand));


    // #pragma pack(push,1)
    // typedef struct PingResponse{
    //     std::array<byte, 2> params = {'1','1'};
    // }PingResponse;
    // #pragma pack(pop)
    // static_assert(2 == sizeof(PingResponse));


    // typedef struct InitCommand{
    //     std::array<byte, 5> params = {'0','0','0','5','1'};
    // }InitCommand;
    // static_assert(5 == sizeof(InitCommand));
    // typedef struct TransmissionReading{
        
    // }TransmissionReading;

    class Command
    {
        private:
            char _context[MAX_LEN_OF_COMMAND];
            size_t _size = 0;
        public:
            Command() = default;
            Command(char* command, size_t size)
            {
                assign(command, size);
            }
            void assign(char* command, size_t size) noexcept
            {
                if (size >= MAX_LEN_OF_COMMAND)
                    size = MAX_LEN_OF_COMMAND;
                
                memcpy(_context, command, size);
                _size = size;
            }
            bool available() const noexcept
            {
                return _size > 0;
            }
            bool is_identical(Command cmd2) const noexcept
            {
                return _size == cmd2._size && !memcmp(_context, cmd2._context, _size);
            }
            size_t size() const noexcept
            {
                return _size;
            }
            const char* getCommand() const noexcept
            {
                return _context;
            }
            void reset()
            {
                _size = 0;
            }
    };

    #pragma pack(push, 1)
    typedef struct ArrangedFloat
    {
        byte bytes_[3];
    }ArrangedFloat;
    #pragma pack(pop)
    static_assert(sizeof(ArrangedFloat) == 3);

    inline char* pack_float(float sample) ///< Packs the float in a big ednian manner
    {
        char const * p = reinterpret_cast<char const *>(&sample); ///> cast float into byte array
        ArrangedFloat arrangedFloat = {p[2], p[1], p[0]}; ///> rearrange the bytes as big endian
        return reinterpret_cast<char *>(&arrangedFloat);
    }
}

#endif
