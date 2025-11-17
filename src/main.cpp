#include "lightcontrol.h"
#include "Konfiguration.h"
#include "Boundary.h"

Konfiguration system_config(30);
IR_sensor Infraroed_sensor(PIR_PIN);
Lyssensor lux_sensor;
LED led(LED_PIN);

light_control system_control(system_config, Infraroed_sensor, lux_sensor, led);

OverrideState manuel_tilstand = AUTO;

unsigned long previousMillis = 0;
const unsigned long PAUSEN_MS = 5000;

void setup() {
    Serial.begin(115200);
    Infraroed_sensor.IR_init();
    lux_sensor.lyssensor_init();
    led.setup();
    Serial.println("LET'SARGO");
}

void loop() {
    unsigned long currentMillis = millis();
    
    if (manuel_tilstand == AUTO) {
        system_control.run_auto_logic(currentMillis);
    } else {
        system_control.run_manual_override(manuel_tilstand, currentMillis);
    }
    
    if (currentMillis - previousMillis >= PAUSEN_MS) {
        previousMillis = currentMillis;
        
        Serial.print("Lux: ");
        Serial.print(lux_sensor.getluxlevel());
        Serial.print("");
    }
}