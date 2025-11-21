#ifndef KONFIGURATION_H
#define KONFIGURATION_H

#include <Arduino.h>

const unsigned long time_until_light_needs_to_turn_off = 15000;
class Konfiguration {
protected:
    int lys_taerskel_val;
private:
    unsigned long timer_ms;
    int max_lux_scale;
public:
    Konfiguration();
    Konfiguration(int taerskel);
    int lys_taerskel() const;
    unsigned long get_hold_time() const;
    int get_max_lux_scale() const;
};

#endif