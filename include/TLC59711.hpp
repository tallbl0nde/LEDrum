#ifndef TLC59711_HPP
#define TLC59711_HPP

#include <cstdint>
#include <string>

// Forward declare SPI class
namespace GPIO {
    class SPI;
};

// Class representing the TLC59711 PWM controller, allowing
// for setting the value of each channel.
class TLC59711 {
    public:
        // Available Chip Select pins
        enum class ChipSelect {
            CS0 = 0,      // Channel 0 (pin 8)
            CS1 = 1       // Channel 1 (pin 7)
        };

        // Colour component
        enum class Component {
            Red   = 0,
            Green = 1,
            Blue  = 2
        };

        // Number of channels
        static const size_t Channels = 4;

    private:
        // String describing error occurred
        std::string error_;

        // SPI object used for communication
        GPIO::SPI * spi;

        // 2D array containing channels and their values
        uint16_t values[4][3];

    public:
        // Constructs a new TLC59711 object using the requested Chip Select pin.
        TLC59711(const ChipSelect csPin);

        // Returns a string describing the fatal error encountered.
        // An empty string is returned if no errors have occurred.
        std::string error();

        // Sets the RGB values for the required channel.
        // Expects input in the form [Red, Green, Blue].
        // This change is not sent to the chip until writeChip() is called.
        void setRGB(const unsigned char channel, const uint16_t values[3]);

        // Sets the value for the required channel and component.
        // This change is not sent to the chip until writeChip() is called.
        void setValue(const unsigned char channel, const Component component, const uint16_t value);

        // Writes the current values to the physical chip.
        bool writeChip();
};

#endif
