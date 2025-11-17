#include "Konfiguration.h"

Konfiguration::Konfiguration(int taerskel)
    : lys_taerskel_val(taerskel),
      hold_time_ms(VENTETID_MS),
      max_lux_scale(500) {}

int Konfiguration::lys_taerskel() const {
    return lys_taerskel_val;
}

unsigned long Konfiguration::get_hold_time() const {
    return hold_time_ms;
}

int Konfiguration::get_max_lux_scale() const {
    return max_lux_scale;
}