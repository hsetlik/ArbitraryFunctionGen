#ifndef READOUT_H
#define READOUT_H
#include <Adafruit_SSD1306.h>
#define SDA 21
#define SCL 22
// Abstraction for the SSD1306 display
class Readout
{
private:
    Adafruit_SSD1306 display;
    void bootMessage();
public:
    Readout(/* args */);
    ~Readout();
    void begin(); //call this inside setup, used to boot display and set up I2C
};

#endif // !READOUT_H