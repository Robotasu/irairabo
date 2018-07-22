enum State { S_INIT, S_REALY, S_RUN, S_STOP };

// ゲーム主状態
int state;
// プレイヤー状態
int state_hp;
bool state_isHit;
bool state_isInvicible;

void setup(){
    // 状態初期化
    state = S_INIT;
    state_hp = 3;
    state_isHit = false;
    state_isInvicible = false;

    //
    state =  S_REALY;
}

void loop(){
    // 準備完了中の処理
    if (state == S_REALY) {
        return;
    }
    // プレイ中の処理
    if (state == S_RUN) {
        state = state_update(); // 状態更新処理
        run_loop();
        return;
    }
    // プレイ終了時の処理
    if (state == S_STOP) {
        // リセットボタンを押されたか確認
        state = check_reset_btn();
        // リセットボタンが押されたならリセット
        if (state = S_REALY) {
            reset();
        }
        return;
    }
}

// プレイヤー状態の更新
int state_update() {
    static const unsigned long invicible_time = 1000;
    static unsigned long last_hit_time = millis();

    // TODO: update state_isHit

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
            state_hp--; // hp減少
            state_isInvicible = true; // 無敵時間に入る
            last_hit_time = millis();
        }
    }

    // 残機が0ならストップ
    if (state_hp == 0) return S_STOP;
    // そうでないなら続行
    else return S_RUN;
}

// ゲーム状態の更新
void run_loop() {
    // HPをLEDに反映
    update_led(state_hp);

    // 再生音楽の変更
    update_sound(state_hp, state_isHit);

    // リレーの状態
    update_relay(state_isHit);
}