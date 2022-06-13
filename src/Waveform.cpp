#include "Waveform.h"

Waveform::Waveform()
{
    calculateTable();
}

Waveform::~Waveform() {}
//====================================================
void Sine::calculateTable()
{
    for (uint16_t s = 0; s < TABLE_SAMPLES; ++s)
    {
        float phase = (float) s / (float)TABLE_SAMPLES;
        phase *= TWO_PI;
        table[s] = 4095 * phase;
    }
}
//====================================================
void Triangle::calculateTable()
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