#include "pin.hpp"

namespace pin {

void setup() {
  pinMode(PIN_O_LED_0, OUTPUT);
  pinMode(PIN_O_LED_1, OUTPUT);
  pinMode(PIN_O_LED_2, OUTPUT);
  pinMode(PIN_O_RELAY, OUTPUT);
  pinMode(PIN_O_LED_GAMEOVER, OUTPUT);
  
  pinMode(PIN_I_HIT, INPUT_PULLUP); //INPUT or INPUT_PULLUP ??
}

} // pin