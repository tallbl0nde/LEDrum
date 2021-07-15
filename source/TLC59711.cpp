#include "gpio/SPI.hpp"
#include "TLC59711.hpp"

TLC59711::TLC59711(const ChipSelect csPin) {
    this->error_ = "";
    this->spi = nullptr;

    for (size_t i = 0; i < TLC59711::Channels; i++) {
        this->values[i][0] = 0;
        this->values[i][1] = 0;
        this->values[i][2] = 0;
    }

    // Ensure we have a valid pin
    if (csPin != ChipSelect::CS0 && csPin != ChipSelect::CS1) {
        this->error_ = GPIO::SPI::interpretResult(GPIO::SPI::Result::BadChannel);
        return;
    }

    // Open SPI channel
    GPIO::SPI::ChipSelect chipSelect = (csPin == ChipSelect::CS0 ? GPIO::SPI::ChipSelect::CS0 : GPIO::SPI::ChipSelect::CS1);
    this->spi = new GPIO::SPI(GPIO::SPI::Interface::Main, chipSelect, 10000000);
    if (this->spi->initializeResult() != GPIO::SPI::Result::OK) {
        this->error_ = GPIO::SPI::interpretResult(this->spi->initializeResult());
        return;
    }
}

std::string TLC59711::error() {
    return this->error_;
}

void TLC59711::setRGB(const unsigned char channel, const uint16_t values[3]) {
    // Ensure channel is within range
    if (channel >= TLC59711::Channels) {
        return;
    }

    this->values[channel][static_cast<int>(Component::Red)]   = values[0];
    this->values[channel][static_cast<int>(Component::Green)] = values[1];
    this->values[channel][static_cast<int>(Component::Blue)]  = values[2];
}

void TLC59711::setValue(const unsigned char channel, const Component component, const uint16_t value) {
    // Ensure channel is within range
    if (channel >= TLC59711::Channels) {
        return;
    }

    // Ensure component is within range
    if (component != Component::Red && component != Component::Green && component != Component::Blue) {
        return;
    }

    this->values[channel][static_cast<int>(component)] = value;
}

bool TLC59711::writeChip() {
    // Abort if we had an error
    if (this->error_.empty()) {
        return -1;
    }

    // Form message
    uint8_t buffer[28] = {0};

    // Set write command and full brightness
    buffer[0] = 0b10010100;
    buffer[1] = 0b00011111;
    buffer[2] = 0b11111111;
    buffer[3] = 0b11111111;

    // Encode colours
    for (size_t c = 0; c < TLC59711::Channels; c++) {
        size_t idx = 4 + (6 * (3 - c));

        buffer[idx]   = this->values[c][static_cast<int>(Component::Blue)] >> 8;
        buffer[idx+1] = this->values[c][static_cast<int>(Component::Blue)];
        buffer[idx+2] = this->values[c][static_cast<int>(Component::Green)] >> 8;
        buffer[idx+3] = this->values[c][static_cast<int>(Component::Green)];
        buffer[idx+4] = this->values[c][static_cast<int>(Component::Red)] >> 8;
        buffer[idx+5] = this->values[c][static_cast<int>(Component::Red)];
    }

    // Send to chip
    return (this->spi->writeBytes(buffer, sizeof(buffer)) == sizeof(buffer));
}
