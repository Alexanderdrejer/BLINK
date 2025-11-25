#ifndef KONFIGURATION_H
#define KONFIGURATION_H

#include <Arduino.h>

const unsigned long time_until_light_needs_to_turn_off = 15000;
class Konfiguration {
private:
    int lys_taerskel_val;
    unsigned long timer_ms;
public:
    Konfiguration();
    Konfiguration(int taerskel);
    int lys_taerskel() const;
    unsigned long get_hold_time() const;
};

#endif