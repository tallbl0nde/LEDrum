#ifndef MCP3008_HPP
#define MCP3008_HPP

#include <string>

// Forward declare SPI class
namespace GPIO {
    class SPI;
};

// Class representing the MCP3008 ADC, permitting querying
// the values of each channel.
class MCP3008 {
    public:
        // Available Chip Select pins
        enum class ChipSelect {
            CS0 = 0,      // Channel 0 (pin 8)
            CS1 = 1       // Channel 1 (pin 7)
        };

    private:
        // String describing error occurred
        std::string error_;

        // SPI object used for communication
        GPIO::SPI * spi;

    public:
        // Constructs a new MCP3008 object using the requested Chip Select pin.
        MCP3008(const ChipSelect csPin);

        // Returns a string describing the fatal error encountered.
        // An empty string is returned if no errors have occurred.
        std::string error();

        // Reads the current analog value (0 - 1023) on the requested channel (0 - 7).
        // Returns a negative number if an error occurred.
        short readChannel(const unsigned char channel);

        // Cleans up the MCP3008 object.
        ~MCP3008();
};

#endif
