#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <Arduino.h>
#include <BH1750.h>
#include <Wire.h>

//DRY konstanter så vi kan ændre dem når vi skal på mega2560.
const int LED_PIN = 4;
const int PIR_PIN = 12;

const int SCL_PIN = 22; // Vælger pins til I2C kommunikation.
const int SDA_PIN = 21; // De kan undlades, men synes det er bedst at have dem med.

const int LED_CHANNEL = 0; // Bruges til opsætning af PWM på ESP32. Skal vælge kanal, frekvens og opløsning. 
const int FREQUENCY = 5000; // Sætter frekvensen for PWM til 5 kHz. Teorien er at under 5000 hZ og så blinker det. Fjernes på mega2560.
const int OPLOESNING = 8; // Kan vist fjernes på mega2560.

class IR_sensor {
private:
    bool presence;
    const int pin;
public:
    IR_sensor(int pir_pin); // Pin som IR-sensoren er sat til.
    bool IR_init(); // Sætter bare pin og til input.
    bool getPresence(); // læser presence.
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