#include "Waveform.h"

Waveform::Waveform()
{
}

Waveform::~Waveform() {}


uint16_t Waveform::tick()
{
    static uint16_t tableSample = 0;
    static uint32_t outputSample = 0;
    static uint32_t lastAdvanceSample = 0;
    outputSample = (outputSample + 1) % SAMPLE_RATE_HZ;
    static bool needsAdvance = false;
    if (outputSample > lastAdvanceSample)
        needsAdvance = (outputSample - lastAdvanceSample) > (SAMPLE_RATE_HZ / frequencyHz);
    else
        needsAdvance = ((outputSample + SAMPLE_RATE_HZ) - lastAdvanceSample) > (SAMPLE_RATE_HZ / frequencyHz);
    if (needsAdvance)
    {
        lastAdvanceSample = outputSample;
        tableSample = (tableSample + 1) % TABLE_SAMPLES;
    }
    return table[tableSample];
}
//====================================================
Sine::Sine()
{
    for (uint16_t s = 0; s < TABLE_SAMPLES; ++s)
    {
        float phase = (float) s / (float)TABLE_SAMPLES;
        phase *= TWO_PI;
        table[s] = 4095 * phase;
    }
}
//====================================================
Triangle::Triangle()
{
    uint16_t level = 0;
    uint16_t increment = 2 * (4095 / TABLE_SAMPLES);
    for (uint16_t s = 0; s < TABLE_SAMPLES; s++)
    {
        if (s < (4095 / 2))
            level += increment;
        else
            level -= increment;
        table[s] = level;
    }
}
//====================================================

Waveform* CreateWaveform::createWaveShape (WaveShape shape)
{
    switch (shape)
    {
        case eSine:
            return new Sine();
        case eTriangle:
            return new Triangle();
        default:
            return new Sine();
    }
}
