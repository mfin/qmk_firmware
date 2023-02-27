#include QMK_KEYBOARD_H
#include "bitc_led.c"

enum custom_keycodes {
    CK_DQUO = SAFE_RANGE,
    CK_TASK_VIEW,
    CK_NEXT_WS,
    CK_PREV_WS,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CK_DQUO:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT("2"));
        }
        break;

    case CK_TASK_VIEW:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_TAB)));
        }
        break;

    case CK_NEXT_WS:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_RIGHT))));
        }
        break;

    case CK_PREV_WS:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_LEFT))));
        }
        break;
    }
    return true;
};

enum combo_events {
  CMB_ESC,
  CMB_DEL,
  CMB_CAPSWORD,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_we[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_io[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_gh[] = {KC_G, KC_H, COMBO_END};

combo_t key_combos[] = {
  [CMB_ESC] = COMBO(combo_we, KC_ESC),
  [CMB_DEL] = COMBO(combo_io, KC_DEL),
  [CMB_CAPSWORD] = COMBO(combo_gh, QK_CAPS_WORD_TOGGLE),
};

enum ferris_layers {
  _BASE,
  _NAVFUN,
  _SYMNUM,
  _MISC
};

#define SPC_2 LT(2, KC_SPC)
#define ENT_1 LT(1, KC_ENT)
#define BSPC_SF RSFT_T(KC_BSPC)
#define TAB_SF LSFT_T(KC_TAB)
#define S_CTL LCTL_T(KC_S)
#define D_GUI GUI_T(KC_D)
#define F_ALT LALT_T(KC_F)
#define J_ALT LALT_T(KC_J)
#define K_GUI GUI_T(KC_K)
#define L_CTL RCTL_T(KC_L)
#define SLSH_ALTGR RALT_T(KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
    KC_Q, KC_W,  KC_E,  KC_R,  KC_T,            KC_Y, KC_U,  KC_I,    KC_O,   KC_P,
    KC_A, S_CTL, D_GUI, F_ALT, KC_G,            KC_H, J_ALT, K_GUI,   L_CTL,  KC_SCLN,
    KC_Z, KC_X,  KC_C,  KC_V,  KC_B,            KC_N, KC_M,  KC_COMM, KC_DOT, SLSH_ALTGR,
                            TAB_SF, ENT_1, SPC_2, BSPC_SF
  ),

  [_NAVFUN] = LAYOUT(
    KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F12,         KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR,
    KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11,         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,
    KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F10,         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS,
                            KC_TRNS, KC_TRNS, MO(3), KC_TRNS
  ),

  [_SYMNUM] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_EQL,  KC_MINS, KC_NUHS,         KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS,
    KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_QUOT,         KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS,
    KC_NUBS, KC_RBRC, KC_RCBR, KC_RPRN, CK_DQUO,         KC_0,    KC_1, KC_2, KC_3, KC_TRNS,
                                     KC_TRNS, MO(3), KC_TRNS, KC_TRNS
  ),

  [_MISC] = LAYOUT(
    QK_BOOT, KC_TRNS, CK_PREV_WS, CK_NEXT_WS, CK_TASK_VIEW,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_CAPS,    KC_TRNS,              KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_VOLD,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,              KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_MUTE,
                                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

void housekeeping_task_user(void) {
    if (IS_LAYER_ON(_MISC)) {
        set_bitc_LED(LED_ON);
    } else if (IS_LAYER_ON(_NAVFUN) && !is_keyboard_left()) {
        set_bitc_LED(LED_ON);
    } else if (IS_LAYER_ON(_SYMNUM) && is_keyboard_left()) {
        set_bitc_LED(LED_ON);
    } else {
        set_bitc_LED(LED_OFF);
    }
}
