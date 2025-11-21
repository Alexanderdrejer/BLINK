#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <Arduino.h>
#include <BH1750.h>
#include <Wire.h>

const int LED_PIN = 3;
const int PIR_PIN = A0;

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
#endif