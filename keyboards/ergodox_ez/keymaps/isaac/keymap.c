#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  RGB_SLD,
  TMUX_COPYMODE,
  TMUX_PASTE,
};

// 7
// 7
// 6
// 7
// 5
// 2
// 1
// 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Norman and friends
  [0] = LAYOUT_ergodox(
                       // Left
                       TG(1) , KC_1 , KC_2 , KC_3 , KC_4 , KC_5 , TMUX_COPYMODE ,

                       KC_TAB , KC_Q , KC_W , KC_D , KC_F , KC_K , KC_ESCAPE ,
                       LT(2 , KC_ESCAPE) , KC_A , KC_S , KC_E , KC_T , KC_G ,
                       KC_LSPO , CTL_T( KC_Z ) , LT(2, KC_X) , KC_C , KC_V , KC_B , LT(4, KC_BSPACE) ,

                       CTL_T(KC_NO) , KC_TRANSPARENT , SCMD_T(KC_NO) , ALT_T(KC_NO) , KC_LGUI ,
                       KC_0 , KC_DLR ,
                       KC_RIGHT ,
                       SFT_T(KC_SPACE) , LT(4, KC_TAB ), KC_LEFT ,

                       // Right
                       TMUX_PASTE , KC_6 , KC_7 , KC_8 , KC_9 , KC_0 , TG(3) ,

                       OSM(MOD_LSFT) , KC_J , KC_U , KC_R , KC_L , KC_SCOLON , KC_BSPACE ,
                       KC_Y , KC_N , KC_I , KC_O , LT(2 , KC_H) , LT(4, KC_QUOTE ) ,
                       KC_UP , KC_P , KC_M , KC_COMMA , KC_DOT , LT(3, KC_SLASH ) , KC_RSPC ,

                       CTL_T(KC_NO) , C_S_T(KC_NO) , LGUI(KC_H) , LGUI(KC_L) , KC_DOWN ,
                       KC_TRANSPARENT , KC_DELETE ,
                       KC_LALT ,
                       // enter->qwerty is nice for vim bindings
                       KC_LGUI , KC_BSPACE , LT(1, KC_ENTER)
                       ),

  // QWERTY
  [1] = LAYOUT_ergodox(
                       // Left
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,

                       KC_TRANSPARENT , KC_Q , KC_W , KC_E , KC_R , KC_T , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_A , KC_S , KC_D , KC_F , KC_G ,
                       KC_TRANSPARENT , KC_Z , KC_X , KC_C , KC_V , KC_B , KC_TRANSPARENT ,

                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,

                       // Right
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,

                       KC_TRANSPARENT , KC_Y , KC_U , KC_I , KC_O , KC_P , KC_TRANSPARENT ,
                       KC_H , KC_J , KC_K , KC_L , LT(2, KC_SCOLON ) , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_N , KC_M , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,

                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT
                       ),

  // Symbols
  [2] = LAYOUT_ergodox(
                       // Left
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_PERC , KC_CIRC , KC_LBRACKET , KC_RBRACKET , KC_BSLASH , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_AT , KC_DLR , KC_LCBR , KC_RCBR , KC_LABK ,
                       KC_TRANSPARENT , KC_TRANSPARENT, KC_TRANSPARENT , KC_LPRN , KC_RPRN , KC_GRAVE , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_NONUS_HASH , KC_TRANSPARENT ,
                       KC_TRANSPARENT ,
                       KC_COLN , KC_TRANSPARENT , KC_TRANSPARENT ,
                       // right
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_KP_PLUS , KC_TILD , KC_MINUS , KC_EXLM , KC_TRANSPARENT , KC_BSLASH ,
                       KC_RABK , KC_HASH , KC_PIPE , KC_AMPR , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_KP_ASTERISK , KC_UNDS , KC_2 , KC_3 , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_0 , KC_DOT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_SLASH ,
                       KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_EXLM , KC_EQUAL
                       ),


  // Mouse and motion
  [3] = LAYOUT_ergodox(
                       // left
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_MS_WH_LEFT , KC_MS_UP , KC_MS_WH_RIGHT , KC_MS_WH_UP , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_MS_LEFT , KC_MS_DOWN , KC_MS_RIGHT , KC_MS_WH_DOWN ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT ,
                       KC_MS_BTN1 , KC_MS_BTN2 , KC_TRANSPARENT ,
                       // right
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_UP , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_UP , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_LEFT , KC_DOWN , KC_RIGHT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT
                       ),

  // Numpad
  [4] = LAYOUT_ergodox(
                       // Left
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_NONUS_HASH , KC_TRANSPARENT ,
                       KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       // right
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_7 , KC_8 , KC_9 , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_4 , KC_5 , KC_6 , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_1 , KC_2 , KC_3 , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_0 , KC_DOT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT ,
                       KC_TRANSPARENT ,
                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT

)

};

bool suspended = false;
const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
  case TMUX_COPYMODE:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"[")
    }
    // else is event released
  case TMUX_PASTE:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"]")
    }
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
