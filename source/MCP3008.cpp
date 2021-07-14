#include "gpio/SPI.hpp"
#include "MCP3008.hpp"

MCP3008::MCP3008(const ChipSelect csPin) {
    this->error_ = "";
    this->spi = nullptr;

    // Ensure we have a valid pin
    if (csPin != ChipSelect::CS0 && csPin != ChipSelect::CS1) {
        this->error_ = GPIO::SPI::interpretResult(GPIO::SPI::Result::BadChannel);
        return;
    }

    // Open SPI channel
    GPIO::SPI::ChipSelect chipSelect = (csPin == ChipSelect::CS0 ? GPIO::SPI::ChipSelect::CS0 : GPIO::SPI::ChipSelect::CS1);
    this->spi = new GPIO::SPI(GPIO::SPI::Interface::Main, chipSelect, 1000000);
    if (this->spi->initializeResult() != GPIO::SPI::Result::OK) {
        this->error_ = GPIO::SPI::interpretResult(this->spi->initializeResult());
        return;
    }
}

std::string MCP3008::error() {
    return this->error_;
}

short MCP3008::readChannel(const unsigned char channel) {
    // Ensure we have a valid channel
    if (channel > 7) {
        return -1;
    }

    // Ensure the SPI device is ready
    if (!this->error_.empty()) {
        return -2;
    }

    // Create read/write buffer with request channel number
    uint8_t ch = (0x80 | ((channel & 7) << 4));
    uint8_t buffer[] = {1, ch, 0};
    size_t count = this->spi->transferBytes(buffer, buffer, sizeof(buffer));
    if (count != sizeof(buffer)) {
        return -3;
    }

    // Convert read value
    short value = (buffer[1] & 3) << 8;
    value |=  buffer[2];
    return value;
}

MCP3008::~MCP3008() {
    delete this->spi;
}
