#include QMK_KEYBOARD_H
#include "bitc_led.c"

enum custom_keycodes {
    DOUBLE_QUOTE = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DOUBLE_QUOTE:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT("2"));
        }
        break;
    }
    return true;
};

enum combo_events {
  CMB_ESC,
  CMB_TAB,
  CMB_LPRN,
  CMB_LCBR,
  CMB_RPRN,
  CMB_RCBR,
  CMB_BSPC,
  CMB_DEL,
  CMB_LBRC,
  CMB_RBRC,
  CMB_QUOT,
  CMB_DQT,
  CMB_MINS,
  CMB_UNDS,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_qw[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_as[] = {KC_A, KC_S, COMBO_END};

const uint16_t PROGMEM combo_we[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_sd[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_er[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_df[] = {KC_D, KC_F, COMBO_END};

const uint16_t PROGMEM combo_ui[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM combo_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_mc[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_cd[] = {KC_COMM, KC_DOT, COMBO_END};

const uint16_t PROGMEM combo_op[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_lcol[] = {KC_L, KC_SCLN, COMBO_END};

combo_t key_combos[] = {
  [CMB_TAB] = COMBO(combo_qw, KC_TAB),
  [CMB_LPRN] = COMBO(combo_ui, KC_LPRN),
  [CMB_LCBR] = COMBO(combo_jk, KC_LCBR),
  [CMB_RPRN] = COMBO(combo_io, KC_RPRN),
  [CMB_RCBR] = COMBO(combo_kl, KC_RCBR),
  [CMB_DEL] = COMBO(combo_op, KC_DEL),
  [CMB_LBRC] = COMBO(combo_mc, KC_LBRC),
  [CMB_RBRC] = COMBO(combo_cd, KC_RBRC),
  [CMB_QUOT] = COMBO(combo_we, KC_QUOT),
  [CMB_DQT] = COMBO(combo_er, DOUBLE_QUOTE),
  [CMB_MINS] = COMBO(combo_sd, KC_MINS),
  [CMB_UNDS] = COMBO(combo_df, KC_UNDS),
};

enum ferris_layers {
  _BASE,
  _SYMBOL,
  _EXTEND,
  _FUNCTION
};

#define KC_CTSC RCTL_T(KC_SCLN)
#define KC_CTLA LCTL_T(KC_A)
#define KC_LALZ LALT_T(KC_Z)
#define KC_GUSL GUI_T(KC_SLSH)
#define KC_SPM2 LT(2, KC_SPC)
#define KC_ENM1 LT(1, KC_ENT)
#define KC_RSBS RSFT_T(KC_BSPC)
#define KC_CLES CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Keymap 0: BASE layer
    *
    * ,-----------------------------.      ,-----------------------------.
    * |  Q  |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |  P  |
    * |-----+-----+-----+-----+-----|      |-----+-----+-----+-----+-----|
    * |  A  |  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  |  ;  |
    * |-----+-----+-----+-----+-----|      |-----+-----+-----+-----+-----|
    * |  Z  |  X  |  C  |  V  |  B  |      |  N  |  M  |  ,  |  .  |  /  |
    * `-----------------------------'      `-----------------------------'
    *                   .-----------.      .-----------.
    *                   | TAB | BSP |      | SPC | ENT |
    *                   '-----------'      '-----------'
    */

  [_BASE] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,
    KC_A, KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN,
    KC_LALZ, KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,  KC_COMM, KC_DOT, KC_GUSL,
                                    KC_CLES, KC_ENM1, KC_SPM2, KC_RSBS
  ),

    /* Keymap 1: SYMBOL layer
    *
    * ,------------------------------------------.      ,----------------------------------------.
    * |  1  |   2    |    3    |    4    |   5   |      |    6   |    7   |   8  |    9    |  0  |
    * |-----+--------+---------+---------+-------|      |--------+--------+------+---------+-----|
    * |  A  |  HOME  |  PG DN  |  PG UP  |  END  |      |  LEFT  |  DOWN  |  UP  |  RIGHT  |  "  |
    * |-----+--------+---------+---------+-------|      |--------+--------+------+---------+-----|
    * |  Z  |   X    |    C    |    V    |   B   |      |   N    |   M    |   ,  |    .    |  /  |
    * `------------------------------------------'      `----------------------------------------'
    *                                .-----------.      .-----------.
    *                                | TAB | BSP |      | SPC | ENT |
    *                                '-----------'      '-----------'
    */

  [_SYMBOL] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT, KC_END,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT,
                                    KC_TRNS, KC_TRNS, MO(3), KC_TRNS
  ),

    /* Keymap 2: RAISE layer
    *
    * ,-----------------------------.      ,-----------------------------.
    * |  Q  |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |  P  |
    * |-----+-----+-----+-----+-----|      |-----+-----+-----+-----+-----|
    * |  A  |  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  |  ;  |
    * |-----+-----+-----+-----+-----|      |-----+-----+-----+-----+-----|
    * |  Z  |  X  |  C  |  V  |  B  |      |  N  |  M  |  ,  |  .  |  /  |
    * `-----------------------------'      `-----------------------------'
    *                   .-----------.      .-----------.
    *                   | TAB | BSP |      | SPC | ENT |
    *                   '-----------'      '-----------'
    */

  [_EXTEND] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_PIPE,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_UNDS, KC_PLUS, KC_TRNS, KC_TRNS, QK_BOOT,
                                    KC_TRNS, MO(3), KC_TRNS, KC_TRNS
  ),

    /* Keymap 3: FUNCTION layer
    *
    * ,---------------------------------.      ,----------------------------------.
    * |  RESET  |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |  VOL UP  |
    * |---------+-----+-----+-----+-----|      |-----+-----+-----+-----+----------|
    * |    A    |  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  |  VOL DN  |
    * |---------+-----+-----+-----+-----|      |-----+-----+-----+-----+----------|
    * |    Z    |  X  |  C  |  V  |  B  |      |  N  |  M  |  ,  |  .  |    MUTE  |
    * `---------------------------------'      `----------------------------------'
    *                       .-----------.      .-----------.
    *                       | TAB | BSP |      | SPC | ENT |
    *                       '-----------'      '-----------'
    */

  [_FUNCTION] = LAYOUT(
    QK_BOOT,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_VOLU,
    KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_VOLD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_UNDS, KC_PLUS, KC_TRNS, KC_TRNS, KC_MUTE,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

void housekeeping_task_user(void) {
    if (IS_LAYER_ON(_FUNCTION)) {
        set_bitc_LED(LED_ON);
    } else if (IS_LAYER_ON(_SYMBOL) && !is_keyboard_left()) {
        set_bitc_LED(LED_ON);
    } else if (IS_LAYER_ON(_EXTEND) && is_keyboard_left()) {
        set_bitc_LED(LED_ON);
    } else {
        set_bitc_LED(LED_OFF);
    }
}
