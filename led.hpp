#pragma once

#include <Arduino.h>

namespace led {

void update_led(int state_hp) {
  if (state_hp == 3) {
    digitalWrite(PIN_O_LED_0, HIGH);
    digitalWrite(PIN_O_LED_1, HIGH);
    digitalWrite(PIN_O_LED_2, HIGH);
  } else if (state_hp == 2) {
    digitalWrite(PIN_O_LED_0, HIGH);
    digitalWrite(PIN_O_LED_1, HIGH);
    digitalWrite(PIN_O_LED_2, LOW);
  } else if (state_hp == 1) {
    digitalWrite(PIN_O_LED_0, HIGH);
    digitalWrite(PIN_O_LED_1, LOW);
    digitalWrite(PIN_O_LED_2, LOW);
  } else if (state_hp == 0) {
    digitalWrite(PIN_O_LED_0, LOW);
    digitalWrite(PIN_O_LED_1, LOW);
    digitalWrite(PIN_O_LED_2, LOW);
  }
}

} // led
