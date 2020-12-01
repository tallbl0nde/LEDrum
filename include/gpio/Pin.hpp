#ifndef PIN_HPP
#define PIN_HPP

#include <cstddef>

// This file contains the definition of all pins used throughout
// the program.
namespace GPIO {
	// Typedef pin values
	typedef unsigned short PinID;

	namespace Pin {
		// Input pins
		constexpr PinID inPzoSnare = 1;		// Snare piezo
		constexpr PinID inPzoHigh = 2;		// High tom piezo
		constexpr PinID inPzoLow = 3;		// Low tom piezo
		constexpr PinID inPzoFloor = 4;		// Floor tom piezo
		constexpr PinID inPzoBass = 5;		// Bass piezo

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
		// Note that the index of an input matches with their output (where relevant)
		constexpr PinID inputs[] = {inPzoSnare, inPzoHigh, inPzoLow, inPzoFloor, inPzoBass};
		constexpr size_t inputCount = sizeof(inputs);

		constexpr PinID outputs[] = {outMftSnare, outMftHigh, outMftLow, outMftFloor, outMftBass, outMftRed, outMftGreen, outMftBlue};
		constexpr size_t outputCount = sizeof(outputs);
	};
};

#endif
