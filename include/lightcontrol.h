#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include <Arduino.h>
#include "Konfiguration.h"
#include "Boundary.h"

enum OverrideState {
    AUTO,
    SLUK,
    TAEND
};

class light_control {
private:
    Konfiguration& config;
    IR_sensor& pir;
    Lyssensor& lys;
    LED& led;
    unsigned long last_presence;
    bool evaluate_presence();
    
public:
    light_control(Konfiguration& c, IR_sensor& p, Lyssensor& l, LED& d);
    bool is_light_needed() const;
    int determine_PWM_value();
    void run_auto_logic(unsigned long currentMillis);
    void run_manual_override(OverrideState state, unsigned long currentMillis);
};

#endif