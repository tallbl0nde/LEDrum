#ifndef PIN_HPP
#define PIN_HPP

#include <cstddef>

// This file contains the definition of all pins used throughout
// the program.
namespace GPIO {
	// Typedef pin values
	typedef unsigned char PinID;

	namespace Pin {
		// Output pins
		constexpr PinID outMftSnare = 6;	// Snare MOSFET
		constexpr PinID outMftHigh = 7;		// High tom MOSFET
		constexpr PinID outMftLow = 8;		// Low tom MOSFET
		constexpr PinID outMftFloor = 9;	// Floor tom MOSFET
		constexpr PinID outMftBass = 10;	// Bass MOSFET
		constexpr PinID outMftRed = 11;		// LED red channel MOSFET
		constexpr PinID outMftGreen = 12;	// LED green channel MOSFET
		constexpr PinID outMftBlue = 13;	// LED blue channel MOSFET

		// Arrays used for easy iteration of pins
		constexpr PinID outputs[] = {outMftSnare, outMftHigh, outMftLow, outMftFloor, outMftBass, outMftRed, outMftGreen, outMftBlue};
		constexpr size_t outputCount = sizeof(outputs);
	};
};

#endif
