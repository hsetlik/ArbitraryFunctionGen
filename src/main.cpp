#include <Arduino.h>
#include "Readout.h"
#include "InputInterface.h"
#include "SignalOutput.h"
#include <string>

void encTurned(uint8_t idx, bool dir)
{
  std::string logStr = "Encoder " + std::to_string(idx) + " turned " + (dir ? "right" : "left");
  Serial.println(logStr.c_str());


}

Readout readout;
SignalOutput output(&readout);
InputInterface inputs;

//=================================

void setDacValue(uint16_t val)
{
  static uint16_t lastValue = 0;
  if (lastValue != val)
  {
    lastValue = val;
    //TODO: send to DAC hardware here
  }
}

void setup() 
{
  Serial.begin(115200);
  readout.begin();
  inputs.setCallback(encTurned);
}

void loop() 
{
  inputs.tick();
  setDacValue(output.tick());
}