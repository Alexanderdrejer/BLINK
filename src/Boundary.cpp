#include "Boundary.h"
#include <Adafruit_NeoPixel.h>

IR_sensor::IR_sensor(int pir_pin) : pin(pir_pin), presence(false) {}

bool IR_sensor::IR_init() {
    pinMode(pin, INPUT); // Vælger pins og sætter den til input, da IR sensoren skal aflæse.
    return true;
}

bool IR_sensor::getPresence() {
    presence = (digitalRead(pin) == HIGH); // Hvis IR-sensoren er høj, er der tilstedeværelse.
    return presence;
}

Lyssensor::Lyssensor() 
    : lux_level(0) {}

bool Lyssensor::lyssensor_init() {
    //Indsæt SDA_PIN, SCL_PIN hvis vi skifter tilbage til ESP32.
    Wire.begin(); // Initialiserer I2C kommunikation på valgte pins.
    return Lysmaaler.begin();
}

int Lyssensor::getluxlevel() {
    lux_level = Lysmaaler.readLightLevel();
    return lux_level;
}

LED::LED(int led_pin) : pin(led_pin) {}

void LED::setup() {
    pinMode(pin, OUTPUT); // Sætter LED_PIN som output
    TCCR3A = (1 << COM3C1) | (1 << WGM30); 
    TCCR3B = (1 << WGM32) | (1 << CS31);

    // pinMode(pin, OUTPUT);
    // ledcSetup(LED_CHANNEL, FREQUENCY, OPLOESNING); // Vælger timer, frekvens og opløsning.
    // ledcAttachPin(pin, LED_CHANNEL); // Forbinder pin til valgt kanal.

    // pinMode(pin, OUTPUT);
    // ledcSetup(LED_CHANNEL, FREQUENCY, OPLOESNING); // Vælger timer, frekvens og opløsning.
    // ledcAttachPin(pin, LED_CHANNEL); // Forbinder pin til valgt kanal.
}

void LED::setPWM_value(int pwm_value) {
    OCR3C = pwm_value;
}