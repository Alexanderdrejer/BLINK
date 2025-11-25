#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <Arduino.h>
#include <BH1750.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

const int LED_PIN = 3;
const int PIR_PIN = A1;

const int SCL_PIN = 21; 
const int SDA_PIN = 20; 

class IR_sensor {
private:
    bool presence;
    const int pin;
public:
    IR_sensor(int pir_pin); 
    bool IR_init(); 
    bool getPresence(); 
};

class Lyssensor {
private:
    BH1750 Lysmaaler;
    int lux_level;
public:
    Lyssensor();
    bool lyssensor_init();
    int getluxlevel();
};

class LED {
private:
    const int pin;
public:
    LED(int led_pin);
    void setup();
    void setPWM_value(int pwm_value);
};

class LEDDriver
{
public:
    LEDDriver();
    void initLED();
    void setIntensity(int intensity);
    void runSimplePartySequence();
private:
    uint8_t ring1Pin_;
    uint16_t ledsRing1_;
    Adafruit_NeoPixel ring1_;
    int currentIntensity_;
};

#define BH1750_POWER_DOWN 0x00
#define BH1750_POWER_ON 0x01
#define BH1750_RESET 0x07
#define BH1750_DEFAULT_MTREG 69
#define BH1750_MTREG_MIN 31
#define BH1750_MTREG_MAX 254

class Lyssenor2
{
public:
    enum Mode
    {
        UNCONFIG = 0,
        CON_HIGH_RES_MODE = 0x10,
        ONE_HIGH_RES_MODE = 0x20
    };

    void init_lightsensor();
    int getLuxValue();

private:
    int lux_;
};
#endif

