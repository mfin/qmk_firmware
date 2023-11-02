#include QMK_KEYBOARD_H
#include "bitc_led.c"

enum custom_keycodes {
    CK_DQUO = SAFE_RANGE,
    MAC_SCRN,
    MAC_EMOJ
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CK_DQUO:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT("2"));
        }
        break;

    case MAC_SCRN:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(SS_LCMD("4")));
        }
        break;

    case MAC_EMOJ:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LCMD(" ")));
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
  _NAV,
  _SYM,
  _NUM,
  _MISC
};

#define SPC_2 LT(2, KC_SPC)
#define ENT_1 LT(1, KC_ENT)
#define BSPC_SF RSFT_T(KC_BSPC)
#define TAB_3 LT(3, KC_TAB)
#define A_MEH MEH_T(KC_A)
#define S_CTL LCTL_T(KC_S)
#define D_OPT OPT_T(KC_D)
#define F_CMD LCMD_T(KC_F)
#define J_CMD LCMD_T(KC_J)
#define K_OPT OPT_T(KC_K)
#define L_CTL RCTL_T(KC_L)
#define SCLN_MEH MEH_T(KC_SCLN)
#define PREV_WS LCTL(KC_LEFT)
#define NEXT_WS LCTL(KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
    KC_Q,   KC_W,  KC_E,  KC_R,  KC_T,            KC_Y, KC_U,  KC_I,    KC_O,   KC_P,
    A_MEH,  S_CTL, D_OPT, F_CMD, KC_G,            KC_H, J_CMD, K_OPT,   L_CTL,  SCLN_MEH,
    KC_Z,   KC_X,  KC_C,  KC_V,  KC_B,            KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH,
                             TAB_3, ENT_1, SPC_2, BSPC_SF
  ),

  [_NAV] = LAYOUT(
    _______,  _______, PREV_WS, NEXT_WS, _______,         _______, _______, KC_INS,  _______, _______,
    KC_MEH,   KC_LCTL, KC_LOPT, KC_LCMD, _______,         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
    _______,  _______, _______, _______, _______,         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
                                    _______, _______, MO(4), _______
  ),

  [_SYM] = LAYOUT(
    _______, _______, KC_EQL,  KC_MINS, KC_NUHS,         _______, _______, _______, _______, _______,
    KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_QUOT,         _______, KC_LCMD, KC_LOPT, KC_LCTL, KC_MEH,
    KC_NUBS, KC_RBRC, KC_RCBR, KC_RPRN, CK_DQUO,         _______, _______, _______, _______, _______,
                                     _______, MO(4), _______, _______
  ),

  [_NUM] = LAYOUT(
    _______, _______, _______, _______, _______,         KC_PSLS, KC_7, KC_8, KC_9, KC_PMNS,
    KC_MEH,  KC_LCTL, KC_LOPT, KC_LCMD, _______,         KC_PAST, KC_4, KC_5, KC_6, KC_PPLS,
    _______, _______, _______, _______, _______,         KC_0,    KC_1, KC_2, KC_3, KC_DOT,
                                     _______, _______, _______, _______
  ),

  [_MISC] = LAYOUT(
    _______, _______,  _______,  _______, _______,         KC_MUTE, _______, _______, _______, _______,
    _______, MAC_SCRN, MAC_EMOJ, KC_CAPS, _______,         KC_VOLU, KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP,
    _______, _______,  _______,  _______, _______,         KC_VOLD, _______, _______, _______, _______,
                                     _______, _______, _______, QK_BOOT
  )
};

void housekeeping_task_user(void) {
    if (IS_LAYER_ON(_MISC)) {
        set_bitc_LED(LED_ON);
    } else if (IS_LAYER_ON(_NAV) && !is_keyboard_left()) {
        set_bitc_LED(LED_ON);
    } else if (IS_LAYER_ON(_SYM) && is_keyboard_left()) {
        set_bitc_LED(LED_ON);
    } else {
        set_bitc_LED(LED_OFF);
    }
}
