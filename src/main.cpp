#include "lightcontrol.h"
#include "Konfiguration.h"
#include "Boundary.h"

Konfiguration system_config(500); // Skal ændres via GUI. 
IR_sensor infrared_sensor(PIR_PIN);
Lyssensor lux_sensor;
LED led(LED_PIN);

light_control system_control(system_config, infrared_sensor, lux_sensor, led);

OverrideState manuel_tilstand = AUTO;

unsigned long previousMillis = 0;
const unsigned long PAUSEN_MS = 5000;

void setup() {
    Serial.begin(115200);
    infrared_sensor.IR_init();
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