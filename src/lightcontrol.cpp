#include "lightcontrol.h"

light_control::light_control(Konfiguration& c, IR_sensor& p, Lyssensor& l, LED& d, LEDDriver& d2)
    : config(c), pir(p), lys(l), led(d), last_presence(0), den_nye_LED(d2) {}

void light_control::initSystem()
{
    Serial.begin(115200);
    pir.IR_init();
    lys.lyssensor_init();
    led.setup();
    Serial.println("LET'SARGO");
    den_nye_LED.initLED();
}

bool light_control::evaluate_presence() {
    return pir.getPresence();
}

bool light_control::is_light_needed() const {
    return lys.getluxlevel() < config.lys_taerskel();
}

int light_control::determine_PWM_value() {
    int lux = lys.getluxlevel();
    int taerskel = config.lys_taerskel();

    if (lux >= taerskel) {
        return 0;
    }
    
    long pwm = map(lux, 0, taerskel, 255, 0);
    
    return constrain((int)pwm, 0, 255);
}

void light_control::runSystem(OverrideState status_on_enum)
{
    unsigned long currentMillis = millis();
    if (status_on_enum == AUTO) {
        this->run_auto_logic(currentMillis);
    } else {
        this->run_manual_override(status_on_enum, currentMillis);
    }
}

void light_control::run_auto_logic(unsigned long currentMillis) {

    if (evaluate_presence()) { 
        last_presence = currentMillis; 
    } 

    bool is_hold_time_active = (currentMillis - last_presence < config.get_hold_time()); // Tiden hvormed systemet får lov til at holde lyset tændt selvom der ikke er en i rummet.
    int final_pwm = 0;
    int current_lux = lys.getluxlevel();

    if (is_hold_time_active && is_light_needed()) {
        final_pwm = determine_PWM_value();
        den_nye_LED.setIntensity(den_nye_LED.calculateIntensity(current_lux));
    }

    led.setPWM_value(final_pwm);
}

void light_control::run_manual_override(OverrideState state, unsigned long currentMillis) {
    if (evaluate_presence()) {
        last_presence = currentMillis;
    }
    
    bool is_hold_time_active = (currentMillis - last_presence < config.get_hold_time());
    int final_pwm = 0;

    if (!is_hold_time_active) {
        led.setPWM_value(0);
        return;
    }

    if (state == TAEND) {
        final_pwm = 255; 
    } else if (state == SLUK) {
        final_pwm = 0;
    }
    
    led.setPWM_value(final_pwm);
}