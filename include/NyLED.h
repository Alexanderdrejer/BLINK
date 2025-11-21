#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Konfiguration.h"

class LEDDriver : public Konfiguration
{
public:
    LEDDriver();
    LEDDriver(int lux_taerskel_val);
    void initLED();
    void setIntensity(int intensity);
    bool isRunning();
    int calculateIntensity(int lux);
    void runSimplePartySequence();
private:
    uint8_t ring1Pin_;
    uint16_t ledsRing1_;
    Adafruit_NeoPixel ring1_;
    int currentIntensity_;
};
