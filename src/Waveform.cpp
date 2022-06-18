#include "Waveform.h"

Waveform::Waveform()
{
    periodMicros = (unsigned long)1000000.0f / frequencyHz;
    std::string lStr = "Period: " + std::to_string(periodMicros) + " microseconds";
    Serial.println(lStr.c_str());
}

uint16_t Waveform::advance(unsigned long micros)
{
    static unsigned long microsIntoPeriod = 0;
    microsIntoPeriod = (microsIntoPeriod + micros) % periodMicros;
    float phase = (float)microsIntoPeriod / (float)periodMicros;
    uint16_t idx = phase * TABLE_SAMPLES;
    return table[idx];
}
    
void Waveform::setFrequency(float freq)
{
    frequencyHz = freq;
    periodMicros = (unsigned long)1000000.0f / frequencyHz;
    std::string logStr = "Period length: " + std::to_string(periodMicros) + " microseconds";
    Serial.println(logStr.c_str());
}
//====================================================
Sine::Sine()
{
    unsigned long max = 0;
    unsigned long min = LONG_MAX;
    for (uint16_t s = 0; s < TABLE_SAMPLES; ++s)
    {
        float phase = (float) s / (float)TABLE_SAMPLES;
        phase *= TWO_PI;
        table[s] = WAVE_MAX * ((sin(phase) / 2.0f ) + 0.5f);
        if (table[s] > max)
            max = table[s];
        else if (table[s] < min)
            min = table[s];
    }
    std::string logStr = "Sine minimum: " + std::to_string(min) + " Sine Maximum: " + std::to_string(max);
    Serial.println(logStr.c_str());
}
//====================================================
Triangle::Triangle()
{
    const uint16_t delta = WAVE_MAX / (TABLE_SAMPLES / 2); 
    for (uint32_t s = 0; s < TABLE_SAMPLES; s++)
    {
        uint16_t idx = s;
        if (s > TABLE_SAMPLES / 2)
        {
            auto distance = s - (TABLE_SAMPLES / 2);
            idx = (TABLE_SAMPLES / 2) - distance;
        }    
        uint16_t level = idx * delta;
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
