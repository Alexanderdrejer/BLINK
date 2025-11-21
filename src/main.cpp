#include "lightcontrol.h"
#include "Konfiguration.h"
#include "Boundary.h"
#include "NyLED.h"

using namespace std;

Konfiguration system_config(30); // Skal ændres via GUI. 
IR_sensor infrared_sensor(PIR_PIN);
Lyssensor lux_sensor;
LED led(LED_PIN);
LEDDriver NyLED(200);

light_control system_control(system_config, infrared_sensor, lux_sensor, led, NyLED);

OverrideState manuel_tilstand = AUTO;

unsigned long previousMillis = 0;
const unsigned long PAUSEN_MS = 5000;

void setup() {
    system_control.initSystem();
}

void loop() {
    system_control.runSystem(manuel_tilstand);

        
    
    
    //nedenstående er udelukkende til debugging og kan fjernes når systemet er færdigt.
    // unsigned long currentMillis = millis();
    // if (currentMillis - previousMillis >= PAUSEN_MS) {
    //     previousMillis = currentMillis;
        
    //     Serial.print("Lux: ");
    //     Serial.print(lux_sensor.getluxlevel());
    //     Serial.print("");
    // }
}