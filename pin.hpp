#pragma once

#include <Arduino.h>

/* COM */
#define PIN_COM_RX 8
#define PIN_COM_TX 9

/* OUTPUT */
#define PIN_O_LED_GAMEOVER 7

#define PIN_O_RELAY 10
#define PIN_O_LED_0 11
#define PIN_O_LED_1 12
#define PIN_O_LED_2 13

/* INPUT */
#define PIN_I_HIT 6
#define PIN_READ_HIT() ((digitalRead(PIN_I_HIT)==LOW)?true:false)

namespace pin {

void setup();

} // pin
