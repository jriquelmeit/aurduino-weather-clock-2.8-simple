#pragma once

#include <Arduino.h>

// Obtiene el santo del día según el día del mes (1..31) y el mes (1..12).
// El nombre se copia al buffer de salida desde la memoria Flash (PROGMEM).
void getSaintOfTheDay(int day, int month, char* buffer, size_t maxLen);
