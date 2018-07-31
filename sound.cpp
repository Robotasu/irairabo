#include <SoftwareSerial.h>
#include "DFPlayer_Mini_Mp3.h"

#include "sound.hpp"
#include "pin.hpp"

SoftwareSerial DFP_Serial(PIN_COM_RX, PIN_COM_TX); // RX, TX

namespace sound {

void setup () {
  DFP_Serial.begin(9600);
  mp3_set_serial(DFP_Serial);
  mp3_set_volume (0x00); // volume to 0
}

void update_sound(int state_hp, int state_isHit) {
  static unsigned long sleep_time = 0;
  static unsigned long last = millis();
  static bool once = true;
  static struct {int hp; int isHit;} last_state = {state_hp, state_isHit};

  if (last_state.hp != state_hp || last_state.isHit != state_isHit) {
    once = true;
    last_state.hp = state_hp;
    last_state.isHit = state_isHit;
  }

  if (last + sleep_time <= millis()) {
    if (state_isHit) {
      // damage sound
      mp3_set_volume (0x15);
      mp3_play(SOUND_ID_DAMAGE);
      last = millis();
      sleep_time = 1000;
    }
  
    else {
      if (once) {
        mp3_set_volume (0x10);
        switch(state_hp) {
        case 3:
          mp3_play(SOUND_ID_HP3);
          break;
        case 2:
          mp3_play(SOUND_ID_HP2);
          break;
        case 1:
          mp3_play(SOUND_ID_HP1);
          break;
        case 0:
          mp3_play(SOUND_ID_HP0);
          break;
        default:
          // error
          break;
        }
        once = false;
      }
    }
  }
}

} //sound
