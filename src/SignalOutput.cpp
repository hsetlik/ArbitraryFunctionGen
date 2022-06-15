#include "SignalOutput.h"

SignalOutput::SignalOutput(Readout* r) : 
readout(r),
tableSample(0),
waveform(CreateWaveform::createWaveShape(eSine))
{

}

SignalOutput::~SignalOutput()
{
}


uint16_t SignalOutput::tick()
{
    static unsigned long lastAdvance = 0;
    unsigned long now = micros();
    static uint16_t val = 0;
    if (now - lastAdvance > (1000000 / SAMPLE_RATE_HZ))
    {
        val = waveform->tick();
        lastAdvance = now;
    }
    return val;
}


