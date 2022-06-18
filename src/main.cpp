#include <Arduino.h>
#include "Readout.h"
#include "InputInterface.h"
#include "SignalOutput.h"
#include <string>
#include <Adafruit_MCP4725.h>
#include <MCP_DAC.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "Credentials.h"

#define SDA1 4
#define SCL1 5

// server for OTA firmware updates
AsyncWebServer server(80);

Readout readout;
SignalOutput output(&readout);
InputInterface inputs;
MCP4822 dac;

//=================================
void encTurned(uint8_t idx, bool dir)
{
  std::string logStr = "Encoder " + std::to_string(idx) + " turned " + (dir ? "right" : "left");
  Serial.println(logStr.c_str());
  switch (idx)
  {
    case 0:
      output.shiftWaveform(dir);
      break;
    case 1:
      output.shiftFrequency(dir);
      break;
    case 2:
      break;
    default:
      break;
  }
}

void setDacValue(uint16_t val)
{
  static uint16_t lastValue = 0;
  if (lastValue != val)
  {
    lastValue = val;
    dac.analogWrite(val, 0);
  }
}
void initWifi()
{
   WiFi.mode(WIFI_STA);

        auto res = WiFi.begin(Credentials::ID, Credentials::Password);
        if (res == WL_CONNECT_FAILED)
        {
          Serial.println("Connection failed");
        }
        else if (res == WL_NO_SSID_AVAIL)
        {
          
        }
        while (WiFi.status() != WL_CONNECTED)
        {
          delay(100);
          Serial.print("."); 
        }
        auto ip = WiFi.localIP();
        Serial.println(ip.toString());
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(200, "text/plain", "Hi! I am ESP32."); });

}

void setup() 
{
  Serial.begin(115200);
  readout.begin();
  inputs.setCallback(encTurned);
  dac.selectVSPI();
  dac.begin(5);
  initWifi();
  output.shiftWaveform(true);
  output.shiftWaveform(true);
  output.shiftFrequency(false);
}

void loop() 
{
  inputs.tick();
  setDacValue(output.tick());
}