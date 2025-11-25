#include "Konfiguration.h"

Konfiguration::Konfiguration()
{
    lys_taerskel_val = 0;
    timer_ms = 0;
}

Konfiguration::Konfiguration(int taerskel)
    : lys_taerskel_val(taerskel),
      timer_ms(time_until_light_needs_to_turn_off) {}

int Konfiguration::lys_taerskel() const {
    return lys_taerskel_val;
}

unsigned long Konfiguration::get_hold_time() const {
    return timer_ms;
}