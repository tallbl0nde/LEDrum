#ifndef GPIO_PINS_HPP
#define GPIO_PINS_HPP

#include <cstddef>

// This file contains the definition of all pins used throughout
// the program.
namespace GPIO {
    // Typedef pin values
    typedef unsigned short PinID;

    namespace Pin {
        // Output (PWM) pins
        constexpr PinID outMftSnare = 5;    // Snare MOSFET
        constexpr PinID outMftHigh = 6;     // High tom MOSFET
        constexpr PinID outMftLow = 13;     // Low tom MOSFET
        constexpr PinID outMftFloor = 19;   // Floor tom MOSFET
        constexpr PinID outMftBass = 26;    // Bass MOSFET
        constexpr PinID outMftRed = 16;     // LED red channel MOSFET
        constexpr PinID outMftGreen = 20;   // LED green channel MOSFET
        constexpr PinID outMftBlue = 21;    // LED blue channel MOSFET

        // Array used for easy iteration of pins
        // Note that the index of an input matches with their output (where relevant)
        constexpr PinID outputs[] = {outMftSnare, outMftHigh, outMftLow, outMftFloor, outMftBass, outMftRed, outMftGreen, outMftBlue};
        constexpr size_t outputCount = sizeof(outputs);
    };
};

#endif
