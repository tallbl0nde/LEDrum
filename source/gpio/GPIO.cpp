#include "gpio/GPIO.hpp"
#include <pigpio.h>

namespace GPIO {
    bool initialize() {
        return (gpioInitialise() >= 0);
    }

    void cleanup() {
        gpioTerminate();
    }

    void setPinState(const PinID pin, const State state) {
        gpioSetMode(pin, PI_OUTPUT);
        gpioWrite(pin, state == State::Off ? 0 : 1);
    }

    void setPWM(const PinID pin, const uint8_t duty) {
        gpioPWM(pin, duty);
    }
}
