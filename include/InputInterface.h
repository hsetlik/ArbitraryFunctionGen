#ifndef INPUTINTERFACE_H
#define INPUTINTERFACE_H
#include <RotaryEncoder.h>

// Rotary encoder and button pins
#define ADATA 36
#define ACLK 39
#define ASW 34

#define BDATA 35
#define BCLK 32
#define BSW 33

#define CDATA 25
#define CCLK 26
#define CSW 27

typedef void (*EncoderCallback)(uint8_t, bool);

class InputInterface
{
private:
    /* data */
    RotaryEncoder encoderA;
    RotaryEncoder encoderB;
    RotaryEncoder encoderC;
    EncoderCallback encCallback;
public:
    InputInterface(/* args */);
    ~InputInterface();
    // poll the encoders and run appropriate callback
    void tick();
    // assign the callback funciton
    void setCallback(EncoderCallback c) { encCallback = c; }
};


#endif // !INPUTINTERFACE_H