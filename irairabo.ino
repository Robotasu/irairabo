#include "pin.hpp"
#include "button.hpp"
#include "led.hpp"
#include "sound.hpp"
#include "relay.hpp"

enum State { S_INIT, S_REALY, S_RUN, S_STOP };

// ゲーム主状態
int state;
// プレイヤー状態
int state_hp;
bool state_isHit;
bool state_isInvicible;

void setup(){
  pin::setup();
  sound::setup();
  state_reset();
}

// model reset
void state_reset(){
  // 状態初期化
  state = S_INIT;
  state_hp = 3;
  state_isHit = false;
  state_isInvicible = false;
  //
  state =  S_REALY;
}

void state_set_gameover() {
  state_hp = 0;
  state_isHit = false;
  state_isInvicible = false;
}

int state_is_gameover(){
  return (state_hp == 0 && state_isInvicible == false);
}

void loop(){
    int next_state = state_player_update(); // 状態更新処理
    run_loop();

    // 準備完了中の処理
    if (state == S_REALY) {
      // state to S_RUN
      state = S_RUN;
    }
    // プレイ中の処理
    else if (state == S_RUN) {
        
    }
    // プレイ終了時の処理
    else if (state == S_STOP) {
        // リセットボタンを押されたか確認
        state = button::check_reset_btn();
        // リセットボタンが押されたならリセット
        if (state == S_REALY) {
            state_reset();
        }
    }

    state = next_state;
}

// プレイヤー状態の更新(Controller)
int state_player_update() {
    static const unsigned long invicible_time = 2000;
    static unsigned long last_hit_time = millis();

    // physical -> state

    // update state_isHit
    bool hits = true;
    for (int i = 0; i < 10; ++i) hits = hits && PIN_READ_HIT();
    if (hits) {
      state_isHit = 1;
    } else {
      state_isHit = 0;
    }

    // 無敵状態なら
    if (state_isInvicible)
    {
        // 無敵状態の有効時間確認
        if (last_hit_time + invicible_time < millis()) {
            state_isInvicible = false;
        }
    }

    // 通常状態(無敵じゃない)なら
    else
    {
        // 棒が壁にあったら残機を減らす
        if (!state_isInvicible && state_isHit) {
            if (state_hp > 0) state_hp--; // hp減少
            state_isInvicible = true; // 無敵時間に入る
            last_hit_time = millis();
        }
    }

    // 残機が0ならストップ
    if (state_is_gameover()) {
        return S_STOP;
    }
    // そうでないなら続行
    else return S_RUN;
}

// ゲーム状態を反映(View)
int run_loop() {
    /*
      state_hp ---- led
                  +- sound
      state_isHit - relay
    */
    // HPをLEDに反映
    led::update_led(state_hp);

    // 再生音楽の変更
    sound::update_sound(state_hp, state_isHit);

    // リレーの状態
    relay::update_relay(state_isHit);
}

