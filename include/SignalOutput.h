#ifndef SIGNALOUTPUT_H
#define SIGNALOUTPUT_H
// this translates to a ~23 microsecond period for each tableSample
#include "Readout.h"
#include "Waveform.h"
#include <memory>

// Handle signal output, including DAC hardware and input logic handling
class SignalOutput
{
private:
    /* data */
    Readout* const readout;
    uint16_t tableSample;
    std::unique_ptr<Waveform> waveform;
public:
    SignalOutput(Readout* r);
    ~SignalOutput();
    // advance tableSample as needed
    uint16_t tick();
};


#endif // !SIGNALOUTPUT_H
