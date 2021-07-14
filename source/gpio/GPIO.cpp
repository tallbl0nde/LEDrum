#include "gpio/GPIO.hpp"
#include "gpio/Pin.hpp"
#include <pigpio.h>

namespace GPIO {
	bool initialize() {
		return (gpioInitialise() >= 0);
	}

	void cleanup() {
		gpioTerminate();
	}

	bool setOutputPins(const PinID pins[], const size_t count) {
		// Iterate over passed array
		for (size_t i = 0; i < count; i++) {
			if (gpioSetMode(pins[i], PI_OUTPUT) < 0) {
				return false;
			}
		}

		return true;
	}
}
