#include "Readout.h"

Readout::Readout(/* args */)
{
    
  
}

Readout::~Readout()
{
}


void Readout::bootMessage()
{
    display.clearDisplay();
    display.setCursor(5, 5);
    display.setTextColor(SSD1306_WHITE);
    display.print("Signal Generator");
    display.display();
    delay(1500);
    display.clearDisplay();
}

void Readout::begin()
{
    Wire.begin(SCL, SDA);
    if (!display.begin())
        Serial.println("Display not started!");
    bootMessage();
}