#include "Boundary.h"

IR_sensor::IR_sensor(int pir_pin) : pin(pir_pin), presence(false) {}

bool IR_sensor::IR_init() {
    pinMode(pin, INPUT); // Vælger pins og sætter den til input, da IR sensoren skal aflæse.
    return true;
}

bool IR_sensor::getPresence() {
    presence = (digitalRead(pin) == HIGH); // Hvis IR-sensoren er høj, er der tilstedeværelse.
    return presence;
}

Lyssensor::Lyssensor() : lux_level(0) {}

bool Lyssensor::lyssensor_init() {
    Wire.begin(SDA_PIN, SCL_PIN); // Initialiserer I2C kommunikation på valgte pins.
    return Lysmaaler.begin();
}

int Lyssensor::getluxlevel() {
    lux_level = Lysmaaler.readLightLevel();
    if (lux_level < 0) return 0;
    return lux_level;
}

LED::LED(int led_pin) : pin(led_pin) {}

void LED::setup() {
    ledcSetup(LED_CHANNEL, FREQUENCY, OPLOESNING); // Vælger timer, frekvens og opløsning.
    ledcAttachPin(pin, LED_CHANNEL); // Forbinder pin til valgt kanal.
}

void LED::setPWM_value(int pwm_value) {
    ledcWrite(LED_CHANNEL, pwm_value);
}