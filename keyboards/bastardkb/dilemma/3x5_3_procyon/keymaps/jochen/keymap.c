/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
};

enum {
    TD_V_WORD_BACK,
    TD_GRV_TILD,
};

// Automatically enable sniping-mode on the pointer layer.
// #define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_SYM LT(LAYER_SYMBOLS, KC_TAB)
#define ENT_FUN LT(LAYER_FUNCTION, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

void td_v_word_back(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_V);
    } else if (state->count == 2) {
        tap_code16(LALT(LCTL(KC_LEFT)));
    }
}

void td_grv_tild(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_GRV);
    } else if (state->count == 2) {
        tap_code(KC_TILD);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_V_WORD_BACK] = ACTION_TAP_DANCE_FN(td_v_word_back),
    [TD_GRV_TILD] = ACTION_TAP_DANCE_FN(td_grv_tild),
};

// clang-format off
/** \brief Colemak-DH layout (3 rows, 10 columns). */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,
       LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G, KC_M, LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O),
       PT_Z,    RALT_T(KC_X),    KC_C,    KC_D,    TD(TD_V_WORD_BACK),    KC_K,    KC_H, KC_COMM,  RALT_T(KC_DOT), PT_SLSH,
                      ESC_MED, TAB_SYM, SPC_NAV, ENT_FUN, BSP_NUM, KC_MPLY
  ),

/*
 * Layers used on the Dilemma.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
  [LAYER_FUNCTION] = LAYOUT_split_3x5_3(
    KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_SCRL,   KC_F4,   KC_F5,   KC_F6,  KC_F11, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_PAUS,   KC_F1,   KC_F2,   KC_F3,  KC_F10, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
  ),

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
  [LAYER_NAVIGATION] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,KC_LBRC, KC_RBRC, KC_GT, KC_LT,
                      XXXXXXX, XXXXXXX, _______,  KC_ENT, KC_BSPC, KC_DEL
  ),

/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
  [LAYER_MEDIA] = LAYOUT_split_3x5_3(
    XXXXXXX, RM_PREV, RM_TOGG, RM_NEXT, XXXXXXX, XXXXXXX, RM_PREV, RM_TOGG, RM_NEXT, XXXXXXX,
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY, KC_MUTE
  ),

/** \brief Mouse emulation and pointer functions. */
  [LAYER_POINTER] = LAYOUT_split_3x5_3(
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    _______, DRGSCRL, SNIPING, MS_BTN3, XXXXXXX, XXXXXXX, MS_BTN3, SNIPING, DRGSCRL, _______,
                      MS_BTN3, MS_BTN2, MS_BTN1, MS_BTN1, MS_BTN2, MS_BTN3
  ),

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
  [LAYER_NUMERAL] = LAYOUT_split_3x5_3(
    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_0,       KC_1,    KC_2,    KC_3, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
                      KC_DOT, KC_MINS,   KC_DOT, XXXXXXX, _______, XXXXXXX
  ),

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
  [LAYER_SYMBOLS] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CIRC, KC_PERC, KC_ASTR, KC_AMPR, KC_BSLS,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, TD(TD_GRV_TILD),  KC_QUOT, KC_DQUO, KC_EXLM, KC_PLUS,
    XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX, KC_TILD, KC_HASH, KC_AT,   KC_DLR,  KC_PIPE,
                      XXXXXXX, _______, XXXXXXX, KC_MINS, KC_EQL,  KC_UNDS
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE]       = {ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_FUNCTION]   = {ENCODER_CCW_CW(KC_DOWN, KC_UP),    ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [LAYER_NAVIGATION] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_MEDIA]      = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_POINTER]    = {ENCODER_CCW_CW(RM_HUED, RM_HUEU),  ENCODER_CCW_CW(RM_SATD, RM_SATU)},
    [LAYER_NUMERAL]    = {ENCODER_CCW_CW(RM_VALD, RM_VALU),  ENCODER_CCW_CW(RM_SPDD, RM_SPDU)},
    [LAYER_SYMBOLS]    = {ENCODER_CCW_CW(RM_PREV, RM_NEXT),  ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE

#ifdef COMBO_ENABLE
// Combo definitions
const uint16_t PROGMEM delete_word_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM caps_word_combo[]   = {KC_F, KC_U, COMBO_END};
const uint16_t PROGMEM underscore_combo[]  = {KC_P, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(delete_word_combo, LALT(KC_BSPC)),
    COMBO(caps_word_combo, CW_TOGG),
    COMBO(underscore_combo, KC_UNDS),
};

uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);
#endif // COMBO_ENABLE
