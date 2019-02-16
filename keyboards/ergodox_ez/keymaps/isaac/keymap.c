#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"

#define BASE 0 // Norman layout
#define QWIM 1 // qwerty/+vim: hjkl and navigation friends on right hand, with F- keys in top row
#define SYMBOLS 2
#define NUMPAD 3
#define MOTION 4
#define MACROTMUXLAYER 5 // also known as tmux mode
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
  VIM_BUFFER_START,
  VIM_BUFFER_END,
  VIM_VISUAL_BLOCK,
  VIM_DELETE_LINE,
  VIM_INS_LINE_BELOW,
  VIM_INS_LINE_ABOVE,

  // WR: Write
  WR_GITHUBDOTCOM,
  WR_2AND1,
  WR_CODEFENCE,
  WR_ESCAPEDRETURN,
  WR_ESCAPEDDOUBLEQUOTE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Norman and friends
  [BASE] = LAYOUT_ergodox(
                          // TG(QWIM)
                       TMUX_PANE_SELECT , KC_0 , KC_1 , KC_2 , KC_3 , KC_4 , ___ ,

                       KC_TAB , KC_Q , KC_W , KC_D , KC_F , KC_K , VIM_CMD_MODE ,
                       LT(SYMBOLS , KC_ESCAPE) , KC_A , KC_S , KC_E , KC_T , KC_G ,
                       KC_LSPO , CTL_T( KC_Z ) , LT(SYMBOLS, KC_X) , KC_C , KC_V , KC_B , ___ ,

                       ___ , CTL_T(KC_NO) , SCMD_T(KC_NO) , ALT_T(KC_NO) , KC_LGUI ,

                       LT(MOTION, KC_DELETE) , LCS(KC_V) , // hold for motion layer is nice for left-handed scrolling
                       LCS(KC_C) , // left control shift
                       SFT_T(KC_SPACE) , KC_BSPACE , MO(MACROTMUXLAYER) ,

                       ___ , KC_5 , KC_6 , KC_7 , KC_8 , KC_9 , ___ ,

                       // OSM(MOD_LSFT)
                       ___ , KC_J , KC_U , KC_R , KC_L , KC_SCOLON , KC_QUOTE , // note this deviates from normal norman
                       KC_Y , KC_N , KC_I , KC_O , KC_H , MO(SYMBOLS) , // b/c i use symbols a lot and just can't afford to wait 200ms till they kick in
                       KC_BSPACE , KC_P , KC_M , KC_COMMA , KC_DOT , LT(MOTION, KC_SLASH ) , KC_RSPC ,

                       CTL_T(KC_NO) , ALT_T(KC_NO) , ___ , ___ , KC_DOWN ,

                       LGUI(KC_H) , LGUI(KC_L) ,
                       ___ ,
                       MO(MACROTMUXLAYER) , LT(QWIM , KC_TAB) , LT(NUMPAD, KC_ENTER)
                       ),

  // QWIM
  [QWIM] = LAYOUT_ergodox(
                       // Left
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,

                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___ ,

                       // Right
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       KC_H , KC_J , KC_K , KC_L , KC_0 , KC_DLR ,
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,

                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___
                       ),

  // Symbols
  [SYMBOLS] = LAYOUT_ergodox(
                       // Left
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , KC_PERC , KC_QUOTE , KC_GRAVE , KC_TILD , ___ , ___ ,
                       ___ , KC_AT , KC_DLR , KC_LCBR , KC_RCBR , KC_KP_PLUS ,
                       ___ , KC_BSLASH , KC_CIRC , KC_LBRACKET, KC_RBRACKET,  KC_HASH , ___ ,
                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___ ,
                       // right
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       /* ___ , KC_QUOTE , KC_TILD , KC_MINUS , KC_GRAVE , ___ , ___ , */
                             /* KC_HASH, LSFT(KC_QUOTE) , KC_PIPE , KC_AMPR , ___ , ___ , */
                       /* ___ , KC_KP_ASTERISK , KC_UNDS , KC_LABK , KC_RABK , ___ , ___ , */
                       ___ , ___ , KC_EXLM , KC_MINUS , LSFT(KC_QUOTE) , ___ , ___ ,
                       KC_COLN, KC_EQUAL , KC_PIPE , KC_AMPR , ___ , ___ ,
                       ___ , KC_KP_ASTERISK , KC_UNDS , KC_LABK , KC_RABK , ___ , ___ ,
                                              ___ , ___ , ___ , ___ , ___ ,

                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___
                       ),

  // macros todo:
  // \<ENTER>
  // \" // escaped double quote
  // ``` code fence grave

  //

  // Numpad
  [NUMPAD] = LAYOUT_ergodox(
                      // Left
                      ___ , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,
                      ___ , ___ , WR_ESCAPEDDOUBLEQUOTE , ___ , WR_CODEFENCE ,  ___ , ___ ,
                      ___ , WR_2AND1 , ___ , ___ , ___ , ___ ,
                      ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ ,
                      ___ ,
                      ___ , ___ , ___ ,
                      // right
                      KC_F7 , KC_F8 , KC_F9 , KC_F10 , KC_F11 , KC_F12 , ___ ,
                      ___ , KC_KP_PLUS , KC_7 , KC_8 , KC_9 , KC_SLASH , ___ ,
                      KC_KP_ASTERISK , KC_4 , KC_5 , KC_6 , KC_MINUS , WR_ESCAPEDRETURN ,
                      ___ , KC_DOT , KC_1 , KC_2 , KC_3 , KC_0 , KC_ENTER ,
                      ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ ,
                      ___ ,
                      ___ , ___ , ___
                      ),

  // Mouse and motion
  [MOTION] = LAYOUT_ergodox(
                       // left
                       ___ , ___ , ___ , ___ , ___ , LGUI(KC_H) , LGUI(KC_L) ,
                       ___ , ___ , KC_MS_WH_LEFT , KC_MS_UP , KC_MS_WH_RIGHT , KC_MS_WH_UP , LCTL(KC_TAB) ,
                       ___ , ___ , KC_MS_LEFT , KC_MS_DOWN , KC_MS_RIGHT , KC_MS_WH_DOWN ,
                       ___ , ___ , ___ , ___ , ___ , ___ , LCS(KC_TAB) , // LGUI(KC_H) ,
                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       KC_MS_BTN1 , KC_MS_BTN2 , ___ ,
                       // right
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , LCTL(KC_LEFT) , KC_UP , LCTL(KC_RIGHT) , ___ , ___ ,
                       ___ , ___ , KC_LEFT , KC_DOWN , KC_RIGHT , ___ , ___ ,
                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___
                       ),

  [MACROTMUXLAYER] = LAYOUT_ergodox(
                      // Left
                      ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ , ___ , ___ , ___ , KC_Q , TMUX_COPYMODE ,
                      ___ , ___ , ___ , ___ , ___ , WR_GITHUBDOTCOM ,
                      ___ , ___ , ___ , ___ , ___ , ___ , TMUX_PASTE ,
                      ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ ,
                      ___ ,
                      ___ , ___ , ___ ,
                      // right
                      ___ , ___ , ___ , ___ , ___ , ___ , TG(XPLANE) ,
                      TMUX_PSPLITV , ___ , ___ , ___ , ___ , ___ , TMUX_PSPLITH ,
                      ___ , ___ , ___ , ___ , ___ , ___ ,
                      TMUX_PFS , ___ , ___ , ___ , ___ , ___ , ___ ,
                      TMUX_WCREATE , ___ , ___ , TMUX_WKILL , DOEXIT ,
                      TMUX_WP , TMUX_WN ,
                      TMUX_PLAST ,
                      ___ , ___ , ___
                      ),


  [XPLANE] = LAYOUT_ergodox(
                      // Left
                      KC_BSLASH , ___ , ___ , KC_MINUS , KC_R , KC_EQUAL , KC_RETURN , // toggle instrumentation descriptions on hover ; view: zoom out, tilt up, zoom in; contact ATC
                      KC_SCOLON , LSFT(KC_9) , ___ , KC_Q , KC_F , KC_E , KC_1 , // toggle clickable cockpit areas ; view: pan left, tilt down, pan right; flaps up a notch
                      ___ , ___ , ___ , KC_COMMA , KC_UP , KC_DOT , // view: backward, up, forward
                      KC_SPACE , ___ , ___ , KC_LEFT , KC_DOWN , KC_RIGHT , KC_2 , // general action cmd ; view: move left, down, right ; flaps down a notch
                      ___ , ___ , ___ , KC_G , KC_B , // landing gear, brakes
                      KC_8 , KC_0 , // roll trim left, right
                      KC_LBRACKET, // pitch trim down
                      KC_F1 , KC_F2 , KC_RBRACKET , // throttle down, up ; pitch trim up
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

  case WR_GITHUBDOTCOM:
    if (record->event.pressed) {
      SEND_STRING("github.com/");
    }
    return false;
    break;

  case WR_2AND1:
    if (record->event.pressed) {
      SEND_STRING("2>&1");
    }
    return false;
    break;

  case WR_CODEFENCE:
    if (record->event.pressed) {
      SEND_STRING("```");
    }
    return false;
    break;

  case WR_ESCAPEDRETURN:
    if (record->event.pressed) {
      SEND_STRING("\\"SS_TAP(X_ENTER));
    }
    return false;
    break;

  case WR_ESCAPEDDOUBLEQUOTE:
    if (record->event.pressed) {
      SEND_STRING("\\\"");
    }
    return false;
    break;

  case VIM_BUFFER_START:
    if (record->event.pressed) {
      SEND_STRING("gg");
    }
    return false;
    break;

  case VIM_BUFFER_END:
    if (record->event.pressed) {
      SEND_STRING("G");
    }
    return false;
    break;

  case VIM_VISUAL_BLOCK:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("v"));
    }
    return false;
    break;

  case VIM_DELETE_LINE:
    if (record->event.pressed) {
      SEND_STRING("dd");
    }
    return false;
    break;

  case VIM_INS_LINE_BELOW:
    if (record->event.pressed) {
      SEND_STRING("o"SS_TAP( X_ESCAPE )"k");
    }
    return false;
    break;

  case VIM_INS_LINE_ABOVE:
    if (record->event.pressed) {
      SEND_STRING("ko"SS_TAP( X_ESCAPE )"j");
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
