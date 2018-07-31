#pragma once

#include <Arduino.h>

namespace sound {

#define SOUND_ID_DAMAGE 2
#define SOUND_ID_HP3 1
#define SOUND_ID_HP2 1
#define SOUND_ID_HP1 1
#define SOUND_ID_HP0 1

void setup();

void update_sound(int state_hp, int state_isHit);

} // sound
