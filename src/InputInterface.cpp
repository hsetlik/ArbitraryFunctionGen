#include "InputInterface.h"

InputInterface::InputInterface(/* args */) :
encoderA(ADATA, ACLK, RotaryEncoder::LatchMode::FOUR0),
encoderB(BDATA, BCLK, RotaryEncoder::LatchMode::FOUR0),
encoderC(CDATA, CCLK, RotaryEncoder::LatchMode::FOUR0),
encCallback(nullptr)
{

}

InputInterface::~InputInterface()
{
}

    
void InputInterface::tick()
{
    static int posA = 0;
    static int posB = 0;
    static int posC = 0;
    
    encoderA.tick();
    auto aNew = encoderA.getPosition();
    if (aNew != posA)
    {
        encCallback(0, aNew < posA);
        posA = aNew;
    }

    encoderB.tick();
    auto bNew = encoderB.getPosition();
    if (bNew != posB)
    {
        encCallback(0, bNew < posB);
        posB = bNew;
    }

    encoderC.tick();
    auto cNew = encoderC.getPosition();
    if (cNew != posC)
    {
        encCallback(0, cNew < posC);
        posC = cNew;
    }
}