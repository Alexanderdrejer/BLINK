#include "Konfiguration.h"

Konfiguration::Konfiguration(int taerskel)
    : lys_taerskel_val(taerskel),
      timer_ms(time_until_light_needs_to_turn_off),
      max_lux_scale(100) {}

int Konfiguration::lys_taerskel() const {
    return lys_taerskel_val;
}

unsigned long Konfiguration::get_hold_time() const {
    return timer_ms;
}

int Konfiguration::get_max_lux_scale() const {
    return max_lux_scale;
}