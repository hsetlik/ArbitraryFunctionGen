#ifndef WAVEFORM_H
#define WAVEFORM_H
#define TABLE_SAMPLES 1024
#include <Arduino.h>

typedef uint16_t Wavetable[1024];

struct Waveform
{
    Waveform();
    virtual ~Waveform();
    float frequency;
    Wavetable table;
    //this gets callen in the constructor
    virtual void calculateTable()=0;
};

struct Sine : public Waveform
{
    void calculateTable() override;
};

struct Triangle : public Waveform
{
    void calculateTable() override;
};

#endif // !WAVEFORM_H