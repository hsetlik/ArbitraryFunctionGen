#ifndef SIGNALOUTPUT_H
#define SIGNALOUTPUT_H
#define BUFFER_SIZE 512
// this translates to a ~23 microsecond period for each sample
#define SAMPLE_RATE_HZ 44100
#include "Readout.h"

typedef uint16_t SignalBuffer[BUFFER_SIZE];
// Handle signal output, including DAC hardware and input logic handling
class SignalOutput
{
    friend class Readout;
    SignalBuffer currentBuffer;
private:
    /* data */
    Readout* const readout;
public:
    SignalOutput(Readout* r);
    ~SignalOutput();
};


#endif // !SIGNALOUTPUT_H
