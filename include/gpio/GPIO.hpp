#ifndef GPIO_GPIO_HPP
#define GPIO_GPIO_HPP

#include <cstddef>

// This file contains various helpers to interact with the PiGPIO
// library, as well as initialize and clean it up.
namespace GPIO {
	typedef unsigned short PinID;

	// Initialize the GPIO library + pins
	// Returns true on success, false otherwise
	bool initialize();

	// Cleanup the GPIO library
	void cleanup();

	// Set the given array of pins as input/output
	bool setInputPins(const PinID[], const size_t);
	bool setOutputPins(const PinID[], const size_t);
};

#endif
