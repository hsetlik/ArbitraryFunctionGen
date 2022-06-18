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
    // counter variables
    static unsigned long lastMicros = 0;
    static unsigned long now = 0;
    static unsigned long diff = 0;

    now = micros();

    if (lastMicros < now)
        diff = now - lastMicros;
    else
        diff = now + (LONG_MAX - lastMicros);

    lastMicros = now;
    return waveform->advance(diff);        
}

void SignalOutput::shiftFrequency(bool dir)
{
    const float increment = 4.0f;
    auto freq = waveform->getFrequency();
    if (dir)
        freq += increment;
    else
        freq -= increment;
    if (freq > 20000.0f)
        freq = 20000.0f;
    else if (freq < 0.00001f)
        freq = 0.00001f;
    
    if (waveform->getFrequency() != freq)
        waveform->setFrequency(freq);
}

void SignalOutput::shiftWaveform(bool dir)
{
    if (dir)
    {
        auto shape = ((uint8_t)currentWaveShape + 1) % NUM_WAVE_SHAPES;
        currentWaveShape = (WaveShape)shape;
    }
    else
    {
        auto shape = (uint8_t)currentWaveShape - 1;
        if (shape < 0)
            shape += NUM_WAVE_SHAPES; //also needs to change w/ number of waveforms
        currentWaveShape = (WaveShape)shape;
    }
    auto freq = waveform->getFrequency();
    waveform.reset(CreateWaveform::createWaveShape(currentWaveShape));
    waveform->setFrequency(freq);
}