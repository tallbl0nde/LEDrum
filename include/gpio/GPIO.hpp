#ifndef GPIO_GPIO_HPP
#define GPIO_GPIO_HPP

#include <cstddef>
#include "gpio/Pins.hpp"

// This file contains various helpers to interact with the PiGPIO
// library, as well as initialize and clean it up.
namespace GPIO {
    // Enumeration of possible pin states
    enum class State {
        Off,
        On
    };

    // Initialize the GPIO library + pins
    // Returns true on success, false otherwise
    bool initialize();

    // Cleanup the GPIO library
    void cleanup();

    // Set the state of the given pin
    void setPinState(const PinID pin, const State state);

    // Set the PWM duty cycle on the given pin
    void setPWM(const PinID pin, const uint8_t duty);
};

#endif
