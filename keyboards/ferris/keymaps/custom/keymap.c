#include QMK_KEYBOARD_H
#include "bitc_led.c"

enum custom_keycodes {
    CK_DQUO = SAFE_RANGE,
    CK_SEARCH
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CK_DQUO:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT("2"));
        }
        break;

    case CK_SEARCH:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(" "));
        }
        break;
    }
    return true;
};

enum combo_events {
  CMB_ESC,
  CMB_SRC,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_we[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_er[] = {KC_E, KC_R, COMBO_END};

combo_t key_combos[] = {
  [CMB_ESC] = COMBO(combo_we, KC_ESC),
  [CMB_SRC] = COMBO(combo_er, CK_SEARCH),
};

enum ferris_layers {
  _BASE,
  _FIRST,
  _SECOND,
  _THIRD
};

#define KC_SPM2 LT(2, KC_SPC)
#define KC_ENM1 LT(1, KC_ENT)
#define KC_SFBS RSFT_T(KC_BSPC)
#define KC_SFTB LSFT_T(KC_TAB)
#define KC_CTLS LCTL_T(KC_S)
#define KC_GUID GUI_T(KC_D)
#define KC_ALTF LALT_T(KC_F)
#define KC_ALTJ RALT_T(KC_J)
#define KC_GUIK GUI_T(KC_K)
#define KC_CTLL RCTL_T(KC_L)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
    KC_Q, KC_W,    KC_E,    KC_R,    KC_T,            KC_Y, KC_U,    KC_I,    KC_O,    KC_P,
    KC_A, KC_CTLS, KC_GUID, KC_ALTF, KC_G,            KC_H, KC_ALTJ, KC_GUIK, KC_CTLL, KC_SCLN,
    KC_Z, KC_X,    KC_C,    KC_V,    KC_B,            KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                               KC_SFTB, KC_ENM1, KC_SPM2, KC_SFBS
  ),

  [_FIRST] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_TRNS, KC_PSCR, KC_TRNS, KC_INS,  KC_TRNS,         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS,
                                   KC_TRNS, KC_TRNS, MO(3), KC_DEL
  ),

  [_SECOND] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_QUOT,         KC_MINS, KC_NUHS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_NUBS, KC_RBRC, KC_RCBR, KC_RPRN, CK_DQUO,         KC_EQL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                      KC_ESC, MO(3), KC_TRNS, KC_TRNS
  ),

  [_THIRD] = LAYOUT(
    QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

void housekeeping_task_user(void) {
    if (IS_LAYER_ON(_THIRD)) {
        set_bitc_LED(LED_ON);
    } else if (IS_LAYER_ON(_FIRST) && !is_keyboard_left()) {
        set_bitc_LED(LED_ON);
    } else if (IS_LAYER_ON(_SECOND) && is_keyboard_left()) {
        set_bitc_LED(LED_ON);
    } else {
        set_bitc_LED(LED_OFF);
    }
}
