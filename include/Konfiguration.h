#ifndef KONFIGURATION_H
#define KONFIGURATION_H

#include <Arduino.h>

const unsigned long time_until_light_needs_to_turn_off = 15000; // Hvor længe lyset skal forblive tændt eller slukket.
// Ovenstående skal også være konfiguérbart fra GUI.
class Konfiguration {
private:
    int lys_taerskel_val;
    unsigned long timer_ms;
    int max_lux_scale;
public:
    Konfiguration(int taerskel);
    int lys_taerskel() const;
    unsigned long get_hold_time() const;
    int get_max_lux_scale() const;
};

#endif