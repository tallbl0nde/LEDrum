#include "gpio/GPIO.hpp"
#include "gpio/Pin.hpp"
#include <iostream>

int main(void) {
	// Initialize GPIO
	if (!GPIO::initialize()) {
		std::cout << "[GPIO] Failed to initialize library!" << std::endl;
		return -1;
	}

	// Setup input pins
	if (!GPIO::setInputPins(GPIO::Pin::inputs, GPIO::Pin::inputCount)) {
		std::cout << "[GPIO] Couldn't initialize all input pins" << std::endl;
		return -2;
	}

	// Setup output pins
	if (!GPIO::setOutputPins(GPIO::Pin::outputs, GPIO::Pin::outputCount)) {
		std::cout << "[GPIO] Couldn't initialize all output pins" << std::endl;
		return -3;
	}

	// Clean up GPIO + library
	GPIO::cleanup();
	return 0;
}
