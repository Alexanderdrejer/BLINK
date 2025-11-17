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
    int max_scale = config.get_max_lux_scale();

    int scaled_value = map(lux, 0, max_scale, 0, 255);
    scaled_value = constrain(scaled_value, 0, 255);
    
    return 255 - scaled_value;
}

void light_control::run_auto_logic(unsigned long currentMillis) {

    if (evaluate_presence()) { // Hvis der er tilstedeværelse, opdateres den tiden hvori der sidst var tilstedeværelse.
        last_presence = currentMillis; // Skal bruges til at fortlæle hvpr længe lyset skal være tændt.
    }

    bool hold_time_active = (currentMillis - last_presence < config.get_hold_time());
    int final_pwm = 0;

    if (hold_time_active && is_light_needed()) {
        final_pwm = determine_PWM_value();
    }
    
    led.setPWM_value(final_pwm);
}

void light_control::run_manual_override(OverrideState state, unsigned long currentMillis) {
    if (evaluate_presence()) {
        last_presence = currentMillis;
    }
    
    bool hold_time_active = (currentMillis - last_presence < config.get_hold_time());
    int final_pwm = 0;

    if (!hold_time_active) {
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