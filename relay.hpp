#pragma once

#include <Arduino.h>
#include "pin.hpp"

namespace relay {

#define RELAY_DURATION 50

int update_relay(int state_isHit) {
  static unsigned long last = millis();
  static bool hasOn = false;

  if (state_isHit) {
    if (hasOn == false) {
      digitalWrite(PIN_O_RELAY, HIGH);
      hasOn = true;
    }
    last = millis();
  } else {
    if (hasOn == true) {
      if (last + RELAY_DURATION < millis()) {
        digitalWrite(PIN_O_RELAY, LOW);
        hasOn = false;
      }
    }
  }

  return (digitalRead(PIN_O_RELAY) == HIGH);
}

} // relay
