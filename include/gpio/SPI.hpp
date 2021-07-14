#ifndef GPIO_SPI_HPP
#define GPIO_SPI_HPP

#include <cstdint>
#include <string>

namespace GPIO {
    // Class representing an SPI device (wraps pigpio).
    class SPI {
        public:
            // Available chip select pins
            enum class ChipSelect {
                CS0 = 0,        // Channel 0
                CS1 = 1,        // Channel 1
                CS2 = 2         // Channel 2
            };

            // Available SPI interfaces
            enum class Interface {
                Main,           // Main SPI interface (pins 9, 10 + 11)
                Auxiliary       // Aux SPI interface (pins 19, 20 + 21)
            };

            // Initialization results
            enum class Result {
                OK,             // No error
                BadChannel,     // Bad channel passed
                BadFlags,       // Bad flags passed
                BadInterface,   // Invalid interface requested
                BadSpeed,       // Bad transfer rate
                OpenFailed,     // Failed to open device
                NoAux           // No auxiliary interface available
            };

        private:
            // Handle to actual SPI object
            unsigned int handle;

            // Initialization error
            Result result;

        public:
            // Interprets the passed result code and returns a string describing
            // the result.
            static std::string interpretResult(const Result result);

            // Constructs a new SPI device using the requested configuration.
            SPI(const Interface interface, const ChipSelect csPin, const unsigned int baudRate);

            // Returns whether device initialized successfully.
            Result initializeResult();

            // Reads the requested number of bytes into the passed buffer.
            // Returns number of bytes read, or a negative value on an error.
            size_t readBytes(uint8_t * buffer, const size_t count);

            // Simultaneously reads and writes bytes to/from the device.
            // Returns number of bytes transferred, or a negative value on an error.
            size_t transferBytes(uint8_t * readBuffer, uint8_t * writeBuffer, const size_t count);

            // Writes the requested number of bytes.
            // Returns the number of bytes written, or a negative value on an error.
            size_t writeBytes(uint8_t * buffer, const size_t count);

            // Closes the SPI device.
            ~SPI();
    };
};

#endif
