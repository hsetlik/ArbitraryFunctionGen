# Arbitrary Function Generator

A device made for testing circuits, this arbitrary function generator generates an analog voltage representation of any arbitrary periodic function.

## Hardware

The function generator is built around an ESP32 microcontroller development board. The microcontroller is responsible for polling user inputs from three push-button rotary encoders, controlling the SSD1306 OLED display over I2C, and controlling the MCP4822 DAC over SPI.

## Controls and Features

The digital core of the function generator is controlled via three push-button rotary encoders. The encoders are used to set the frequency, wave shape, and wave mode respectively. The DAC output only reaches a maximum of 3.3v, so the device output is driven by an amplifier. The amplifier level and the output impedance are set by knobs on the front panel. A switch toggles the output of the small output speaker on the back of the device.

## Software

The function generator's firmware is written in the Arduino framework and was developed using the PlatformIO environment. The display and output DAC peripherals are controlled via I2C and SPI protocols respectively. The device also takes advantage of the ESP32's built-in WiFi capability to support over-the-air firmware updates.

### Wave tables and signal output

Each output function is defined by an array of discrete values or 'wave table'. Each time the function to update the DAC with the current value of the signal, the phase is determined by the chosen frequency and the Arduino framework's `micros()` function. The phase dictates a non-integer index in the wave table array, which is then used to find the linear interpolation of the sample before and the sample after that non-integer index. This method of wave generation differs from the conventional wave table signal generator in not being limited in output resolution by a sample rate. Thanks to the `micros()` function, the phase- and by extension the output- can be determined at any arbitrary point in time. Rather than updating the output only at predefined intervals, the output is updated as often as the hardware can manage.
