#include "gpio/SPI.hpp"
#include <pigpio.h>

namespace GPIO {
    std::string SPI::interpretResult(const Result result) {
        switch (result) {
            case Result::OK:
                return "No error.";

            case Result::BadChannel:
                return "An invalid channel was requested.";

            case Result::BadFlags:
                return "Invalid flags were used.";

            case Result::BadInterface:
                return "An invalid interface was requested.";

            case Result::BadSpeed:
                return "An invalid baud rate was requested.";

            case Result::OpenFailed:
                return "Couldn't open the SPI device.";

            case Result::NoAux:
                return "This device does not support the auxiliary interface.";

            default:
                return "Unknown result code.";
        }
    }

    SPI::SPI(const Interface interface, const ChipSelect csPin, const unsigned int baudRate) {
        this->handle = -1;
        this->result = Result::OK;

        // Check interface
        if (interface != Interface::Main && interface != Interface::Auxiliary) {
            this->result = Result::BadInterface;
            return;
        }

        // Check channel
        if (csPin != ChipSelect::CS0 && csPin != ChipSelect::CS1 && csPin != ChipSelect::CS2) {
            this->result = Result::BadChannel;
            return;
        }

        // Set up flags
        unsigned int flags = 0x00;
        if (interface == Interface::Auxiliary) {
            flags |= 0x08;
        }

        // Attempt to open device
        this->handle = spiOpen(static_cast<unsigned int>(csPin), baudRate, flags);
        switch (this->handle) {
            case PI_BAD_SPI_CHANNEL:
                this->result = Result::BadChannel;
                break;

            case PI_BAD_SPI_SPEED:
                this->result = Result::BadSpeed;
                break;

            case PI_BAD_FLAGS:
                this->result = Result::BadFlags;
                break;

            case PI_NO_AUX_SPI:
                this->result = Result::NoAux;
                break;

            case PI_SPI_OPEN_FAILED:
                this->result = Result::OpenFailed;
                break;
        }
    }

    SPI::Result SPI::initializeResult() {
        return this->result;
    }

    size_t SPI::readBytes(uint8_t * buffer, const size_t count) {
        return spiRead(this->handle, reinterpret_cast<char *>(buffer), count);
    }

    size_t SPI::transferBytes(uint8_t * readBuffer, uint8_t * writeBuffer, const size_t count) {
        return spiXfer(this->handle, reinterpret_cast<char *>(writeBuffer), reinterpret_cast<char *>(readBuffer), count);
    }

    size_t SPI::writeBytes(uint8_t * buffer, const size_t count) {
        return spiWrite(this->handle, reinterpret_cast<char *>(buffer), count);
    }

    SPI::~SPI() {
        if (this->result == Result::OK) {
            spiClose(this->handle);
        }
    }
};
