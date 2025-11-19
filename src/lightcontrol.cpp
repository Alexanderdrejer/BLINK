#include "lightcontrol.h"

light_control::light_control(Konfiguration& c, IR_sensor& p, Lyssensor& l, LED& d)
    : config(c), pir(p), lys(l), led(d), last_presence(0) {}

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
    // Map funktionen skalere et tal til et andet. 
    // Vi har en sensor der kan give et tal mellem 0 og meget højt lux.
    // Vi har også et signal der skal være mellem 0 og 255. 
    // Map regner forholdet ud, så 1 lux svarer til x pwm. 
    // Eksempelvis: map(50, 0, 100, 0, 255)
    
    return constrain((int)pwm, 0, 255);
}

void light_control::run_auto_logic(unsigned long currentMillis) {

    if (evaluate_presence()) { // Hvis der er tilstedeværelse, opdateres den tiden hvori der sidst var tilstedeværelse.
        last_presence = currentMillis; // Skal bruges til at fortælle hvpr længe lyset skal være tændt.
    } // Skal også sendes til LOG, da det er tidpsunktet for hvornår der sidst var tilstedeværelsn i rumemt

    bool is_hold_time_active = (currentMillis - last_presence < config.get_hold_time()); // Tiden hvormed systemet får lov til at holde lyset tændt selvom der ikke er en i rummet.
    int final_pwm = 0;

    if (is_hold_time_active && is_light_needed()) {
        final_pwm = determine_PWM_value();
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