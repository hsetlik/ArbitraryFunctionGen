#include <Arduino.h>
#include "Readout.h"
#include "InputInterface.h"
#include <string>

void encTurned(uint8_t idx, bool dir)
{
  std::string logStr = "Encoder " + std::to_string(idx) + " turned " + dir ? "right" : "left";
  Serial.println(logStr.c_str());


}

Readout readout;
InputInterface inputs;

void setup() 
{
  Serial.begin(115200);
  readout.begin();
  inputs.setCallback(encTurned);
}

void loop() 
{
  inputs.tick();
}