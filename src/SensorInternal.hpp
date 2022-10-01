namespace SensorInternal{
    const static size_t MAX_LEN_OF_COMMAND = 10; ///< Max length of a command
    class Command
    {
        private:
            char _context[MAX_LEN_OF_COMMAND];
            size_t _size;
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
    };
}
