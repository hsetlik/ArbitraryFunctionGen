#ifndef WAVEFORM_H
#define WAVEFORM_H
#define TABLE_SAMPLES 1024
#define SAMPLE_RATE_HZ 44100
#define NUM_WAVE_SHAPES 2
#include <Arduino.h>
#include <string>

typedef uint16_t Wavetable[TABLE_SAMPLES];

// Waveform base class
struct Waveform
{
    Waveform();
    uint16_t advance(unsigned long us);
    void setFrequency(float freq);
    float getFrequency() { return frequencyHz; }
protected:
    float frequencyHz = 1000.0f;
    Wavetable table;
    unsigned long periodMicros;
};

// Subclasses for each wave shape

struct Sine : public Waveform
{
    Sine();
};

struct Triangle : public Waveform
{
    Triangle();
};

// All the above wave shapes
enum WaveShape
{
    eSine,
    eTriangle
};

//========================================
struct CreateWaveform
{
    static Waveform* createWaveShape(WaveShape shape);
};

#endif // !WAVEFORM_H