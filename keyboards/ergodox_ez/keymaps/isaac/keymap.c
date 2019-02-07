#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"

#define BASE 0 // Norman layout
#define QWERTY 1
#define SYMBOLS 2
#define MOTION 3
#define NUMPAD 4
#define MACROSLAYER 5 // also known as tmux mode
#define XPLANE 6

#define ___ KC_TRANSPARENT

#define LCS(code) LCTL(LSFT(code))

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  RGB_SLD,

  DOEXIT, // type 'exit' and tap enter

  TMUX_COPYMODE,
  TMUX_PASTE,
  TMUX_LEADER,

  TMUX_WN, // window next
  TMUX_WP, // window previous
  TMUX_WCREATE, // create windw
  TMUX_WKILL, // kill window

  TMUX_PANE_SELECT,
  TMUX_PFS, // pane fullscreen == leader,z
  TMUX_PLAST, // pane last active
  TMUX_PSPLITH, // pane split horizontally
  TMUX_PSPLITV, // pane split vertically

  VIM_CMD_MODE,
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
  [BASE] = LAYOUT_ergodox(
                          // TG(QWERTY)
                       TMUX_PANE_SELECT , KC_0 , KC_1 , KC_2 , KC_3 , KC_4 , TMUX_COPYMODE ,

                       KC_TAB , KC_Q , KC_W , KC_D , KC_F , KC_K , VIM_CMD_MODE ,
                       LT(SYMBOLS , KC_ESCAPE) , KC_A , KC_S , KC_E , KC_T , KC_G ,
                       KC_LSPO , CTL_T( KC_Z ) , LT(SYMBOLS, KC_X) , KC_C , KC_V , KC_B , TMUX_LEADER , // TODO

                       TMUX_PANE_SELECT , CTL_T(KC_NO) , SCMD_T(KC_NO) , ALT_T(KC_NO) , KC_LGUI ,

                       KC_0 , KC_DLR ,
                       LCS(KC_C) , // left control shift
                       SFT_T(KC_SPACE) , KC_BSPACE , KC_DELETE ,

                       TMUX_PASTE , KC_5 , KC_6 , KC_7 , KC_8 , KC_9 , TG(XPLANE) ,

                       // OSM(MOD_LSFT)
                       ___ , KC_J , KC_U , KC_R , KC_L , KC_SCOLON , KC_BSPACE ,
                       KC_Y , KC_N , KC_I , KC_O , KC_H , LT(SYMBOLS, KC_QUOTE ) ,
                       KC_UP , KC_P , KC_M , KC_COMMA , KC_DOT , LT(MOTION, KC_SLASH ) , KC_RSPC ,

                       CTL_T(KC_NO) , C_S_T(KC_NO) , LALT(KC_B) , LALT(KC_F) , KC_DOWN ,
                       LGUI(KC_H) , LGUI(KC_L) ,
                       LCS(KC_V) ,
                       MO(MACROSLAYER) , LT(QWERTY, KC_TAB) , LT(NUMPAD, KC_ENTER)
                       ),

  // QWERTY
  [QWERTY] = LAYOUT_ergodox(
                       // Left
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,

                       ___ , KC_Q , KC_W , KC_E , KC_R , KC_T , ___ ,
                       ___ , KC_A , KC_S , KC_D , KC_F , KC_G ,
                       ___ , KC_Z , KC_X , KC_C , KC_V , KC_B , ___ ,

                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___ ,

                       // Right
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,

                       ___ , KC_Y , KC_U , KC_I , KC_O , KC_P , ___ ,
                       KC_H , KC_J , KC_K , KC_L , LT(SYMBOLS, KC_SCOLON ) , ___ ,
                       ___ , KC_N , KC_M , ___ , ___ , ___ , ___ ,

                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___
                       ),

  // Symbols
  [SYMBOLS] = LAYOUT_ergodox(
                       // Left
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , KC_PERC , KC_CIRC , KC_LBRACKET , KC_RBRACKET , KC_BSLASH , ___ ,
                       ___ , KC_AT , KC_DLR , KC_LCBR , KC_RCBR , KC_LABK ,
                       ___ , ___, ___ , KC_LPRN , KC_RPRN , KC_GRAVE , ___ ,
                       ___ , ___ , ___ , ___ , ___ ,
                       KC_NONUS_HASH , ___ ,
                       ___ ,
                       KC_COLN , ___ , ___ ,
                       // right
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , KC_KP_PLUS , KC_TILD , KC_MINUS , KC_EXLM , ___ , KC_BSLASH ,
                       KC_RABK , KC_HASH , KC_PIPE , KC_AMPR , ___ , ___ ,
                       ___ , KC_KP_ASTERISK , KC_UNDS , KC_2 , KC_3 , ___ , ___ ,
                       KC_0 , KC_DOT , ___ , ___ , ___ ,
                       ___ , KC_SLASH ,
                       ___ ,
                       ___ , KC_EXLM , KC_EQUAL
                       ),


  // Mouse and motion
  [MOTION] = LAYOUT_ergodox(
                       // left
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , KC_MS_WH_LEFT , KC_MS_UP , KC_MS_WH_RIGHT , KC_MS_WH_UP , ___ ,
                       ___ , ___ , KC_MS_LEFT , KC_MS_DOWN , KC_MS_RIGHT , KC_MS_WH_DOWN ,
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       KC_MS_BTN1 , KC_MS_BTN2 , ___ ,
                       // right
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , KC_UP , ___ , ___ , ___ ,
                       ___ , ___ , KC_UP , ___ , ___ , ___ ,
                       ___ , ___ , KC_LEFT , KC_DOWN , KC_RIGHT , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___
                       ),

  // Numpad
  [NUMPAD] = LAYOUT_ergodox(
                       // Left
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ ,
                       KC_NONUS_HASH , ___ ,
                       ___ ,
                       ___ , ___ , ___ ,
                       // right
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , KC_KP_PLUS , KC_7 , KC_8 , KC_9 , ___ , ___ ,
                       KC_MINUS , KC_4 , KC_5 , KC_6 , KC_0 , ___ ,
                       ___ , KC_KP_ASTERISK , KC_1 , KC_2 , KC_3 , KC_SLASH , KC_ENTER ,
                       KC_0 , KC_DOT , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___
                            ),

  [MACROSLAYER] = LAYOUT_ergodox(
                            // Left
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ ,
                            ___ ,
                            ___ , ___ , ___ ,
                            // right
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , KC_7 , KC_8 , KC_9 , ___ , TMUX_WKILL ,
                            ___ , KC_0 , KC_4 , KC_5 , KC_6 , ___ ,
                            TMUX_PFS , TMUX_PANE_SELECT , KC_1 , KC_2 , KC_3 , ___ , TMUX_PSPLITH ,
                            ___ , ___ , ___ , ___ , DOEXIT ,
                            TMUX_WP , TMUX_WN ,
                            TMUX_PLAST ,
                            ___ , TMUX_WCREATE , TMUX_PSPLITV
                                 ),


  [XPLANE] = LAYOUT_ergodox(
                            // Left
                            KC_BSLASH , ___ , ___ , KC_MINUS , KC_R , KC_EQUAL , KC_RETURN , // toggle instrumentation descriptions on hover ; view: zoom out, tilt up, zoom in; contact ATC
                            KC_SCOLON , LSFT(KC_9) , ___ , KC_Q , KC_F , KC_E , KC_1 , // toggle clickable cockpit areas ; view: pan left, tilt down, pan right; flaps up a notch
                            ___ , ___ , ___ , KC_COMMA , KC_UP , KC_DOT , // view: backward, up, forward
                            KC_SPACE , ___ , ___ , KC_LEFT , KC_DOWN , KC_RIGHT , KC_2 , // general action cmd ; view: move left, down, right ; flaps down a notch
                            ___ , ___ , ___ , KC_G , KC_B , // landing gear, brakes
                            KC_8 , KC_0 , // roll trim left, right
                            KC_RBRACKET, // pitch trim up
                            KC_F1 , KC_F2 , KC_LBRACKET , // throttle down, up ; pitch trim down
                            // right
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ ,
                            ___ ,
                            ___ , ___ , ___
                            )

/*   [EMPTY] = LAYOUT_ergodox( */
/*                             // Left */
/*                             ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , */
/*                             ___ , */
/*                             ___ , ___ , ___ , */
/*                             // right */
/*                             ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , ___ , ___ , ___ , */
/*                             ___ , ___ , */
/*                             ___ , */
/*                             ___ , ___ , ___ */
/*                             ) */

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
      SEND_STRING(SS_LCTRL("b")"[");
    }
    // else is event released
    return false;
    break;
  case TMUX_PASTE:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"]");
    }
    return false;
    break;
  case TMUX_LEADER:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b"));
    }
    return false;
    break;

  case TMUX_WN:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"n");
    }
    return false;
    break;

  case TMUX_WP:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"p");
    }
    return false;
    break;

  case TMUX_WCREATE:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"c");
    }
    return false;
    break;

  case TMUX_WKILL:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"x");
    }
    return false;
    break;

  case TMUX_PFS:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"z");
    }
    return false;
    break;

  case TMUX_PLAST:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")";");
    }
    return false;
    break;

  case TMUX_PSPLITV:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"%");
    }
    return false;
    break;

  case TMUX_PSPLITH:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"\"");
    }
    return false;
    break;

  case DOEXIT:
    if (record->event.pressed) {
      SEND_STRING("exit"SS_TAP(X_ENTER));
    }
    return false;
    break;

  case VIM_CMD_MODE:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE)":");
    }
    return false;
    break;
  case TMUX_PANE_SELECT:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"q");
    }
    return false;
    break;
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
