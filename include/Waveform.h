#ifndef WAVEFORM_H
#define WAVEFORM_H
#define TABLE_SAMPLES 1024
#define SAMPLE_RATE_HZ 44100
#include <Arduino.h>
#include <string>

typedef uint16_t Wavetable[1024];

// Waveform base class
struct Waveform
{
    Waveform();
    uint16_t tick();
    float frequencyHz = 1000.0f;
protected:
    Wavetable table;
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