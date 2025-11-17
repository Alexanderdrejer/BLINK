#ifndef KONFIGURATION_H
#define KONFIGURATION_H

#include <Arduino.h>

const unsigned long VENTETID_MS = 15000; // Hvor længe lyset skal forblive tændt eller slukket.

class Konfiguration {
private:
    int lys_taerskel_val;
    unsigned long hold_time_ms;
    int max_lux_scale;

public:
    Konfiguration(int taerskel);
    int lys_taerskel() const;
    unsigned long get_hold_time() const;
    int get_max_lux_scale() const;
};

#endif