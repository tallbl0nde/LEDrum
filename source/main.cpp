#include "gpio/GPIO.hpp"
#include <iostream>
#include "MCP3008.hpp"
#include "TLC59711.hpp"
#include <thread>

int main(void) {
    // Initialize GPIO
    if (!GPIO::initialize()) {
        std::cerr << "[GPIO] Failed to initialize library!" << std::endl;
        return -1;
    }

    // Ensure all pins start initially off
    for (GPIO::PinID pin : GPIO::Pin::outputs) {
        GPIO::setPinState(pin, GPIO::State::Off);
    }

    // Create MCP3008 object
    MCP3008 * piezos = new MCP3008(MCP3008::ChipSelect::CS0);
    std::string err = piezos->error();
    if (!err.empty()) {
        std::cerr << "[MCP3008] Couldn't initialize object: " << err << std::endl;
        return -3;
    }

    for (size_t i = 0; i < 100000; i++) {
        short val[] = {0};
        for (size_t c = 0; c < 5; c++) {
            val[c] = piezos->readChannel(c);
            std::cout << c << ": " << val[c] << std::endl;
        }
        std::cout << "===============================" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // Destroy objects
    delete piezos;

    // Clean up GPIO + library
    GPIO::cleanup();
    return 0;
}
