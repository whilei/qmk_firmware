#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"

#define ___ KC_TRANSPARENT

#define LCS(code) LCTL(LSFT(code))
#define LSALT(code) LALT(LSFT(code))
#define CONALT(code) LCTL(LALT(code))
#define CTLGUI(code) LCTL(LGUI(code))

enum {
  BASE = 0, // Norman layout
  CAPSLAYER ,
  TOPROWALT,
  TOPROWNUM,
  NUMPAD ,
  FLAYER ,
  SYMBOLS ,
  MOTIONLAYER ,
  QWIMAMU,  // qwerty/+vim: hjkl and navigation friends on right hand, with F- keys in top row
  GOLANDLAYER ,
  MACROLAYER , // words, and stuff
  XPLANE,
  UNICODEL ,
};

enum {
      TD_CURLYBRACKET = 0,
      TD_PAREN,
      TD_BRACKET,
      TD_QUOTE_COUNTERINTUITIVE,
      TD_HYPHEN_EQUALS,
      TD_HELPFLAG
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  RGB_SLD,

  // Mine/

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
  VIM_NOH,
  VIM_BUFFER_PREV,
  VIM_BUFFER_NEXT,

  // WR: Write
  WR_REDIR_2AND1,
  WR_REDIR_STDERR,
  WR_REDIR_STDOUT,
  WR_IFS_EQ,
  WR_CODEFENCE,
  WR_ESCAPEDRETURN,
  WR_ESCAPEDDOUBLEQUOTE,
  WR_ESCAPEDSINGLEQUOTE,
  WR_DOUBLE_LBRACKET,
  WR_DOUBLE_RBRACKET,
  WR_SHEBANGS_BASH,
  WR_SLASHSLASH,

  WR_FLAGHELP,
  WR_FLAGHELPLESS,

  WR_COLONEQUALS,
  WR_NOTEQUALS,
  WR_EQUALSEQUALS,

  WR_MD_TODO,

  WR_WORD_ETHEREUM,
  WR_WORD_GOETHEREUM,
  WR_WORD_GITHUB_DOT_COM,
  WR_WORD_ETCLABSCORE,
  WR_CD_DEV_ETCLABSCORE,
  WR_WORD_MEOWSBITS,
  WR_WORD_RETURN,
  WR_BUILD_BIN_GETH,
  WR_GETH,
  WR_PIPE_LESS,
  WR_LESS,
  WR_GREP,


  // Emoji.. how am I just getting these
  EMOJI_UHU,
  EMOJI_FACE2,
  EMOJI_FACE1,
  EMOJI_EGGY2,
  EMOJI_SMILE2,
  EMOJI_SHRUG,
  EMOJI_YAY,

  // type long-ish common (top 100 english words)
  WORD_BECAUSE,
  WORD_WOULD,
  WORD_COULD,
  WORD_SHOULD,
  WORD_ABOUT,
  WORD_P2P,

  SPACEMACS_WINDOW_LEFT,
  SPACEMACS_WINDOW_RIGHT,
  SPACEMACS_WINDOW_UP,
  SPACEMACS_WINDOW_DOWN,
  SPACEMACS_NEOTREE_TOGGLE,

  LOCK_SHIFT,

  DYNAMIC_MACRO_RANGE
};
#include "dynamic_macro.h"

void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_LNX);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



  // Norman and friends
  [BASE] = LAYOUT_ergodox(
                       // Left
                       LT( TOPROWALT, KC_TAB ) , KC_UP , LT(MACROLAYER, KC_0) , KC_DLR , KC_KP_ASTERISK , KC_PERC , CTLGUI(KC_K) ,

                       KC_DOUBLE_QUOTE , LT(FLAYER, KC_Q) , KC_W , KC_D , KC_F , KC_K , ___ ,
                       LT(SYMBOLS , KC_ESCAPE) , KC_A , KC_S , KC_E , KC_T , KC_G ,
                       KC_LSHIFT ,  LT( QWIMAMU, KC_Z ) , LT(NUMPAD, KC_X) ,  KC_C  , KC_V , LCTL_T( KC_B ) , MO(GOLANDLAYER) ,

                       KC_MS_WH_DOWN,  CTL_T(KC_NO) , KC_MS_WH_UP , ALT_T(KC_NO) , KC_LGUI ,

                       LT(MOTIONLAYER, KC_DELETE) , TG(MOTIONLAYER) , // hold for motion layer is nice for left-handed scrolling
                       LCTL(KC_TAB) , // browser tab right
                       SFT_T(KC_SPACE) , KC_BSPACE , LCS(KC_TAB) , // browser tab left


                       // Right
                       CTLGUI(KC_J) , KC_COLON , KC_EQUAL , LT(MACROLAYER, KC_MINUS ), KC_UNDS , KC_GRAVE , TG(TOPROWNUM) ,

                       KC_QUESTION , KC_J , KC_U , KC_R , KC_L , LT(FLAYER, KC_SCOLON) , KC_QUOTE ,
                       KC_Y , KC_N , KC_I , KC_O ,  KC_H , MO(SYMBOLS) , // b/c i use symbols a lot, no 200ms wait
                       KC_BSPACE , LGUI_T( KC_P ) , KC_M , ALT_T( KC_COMMA ) , KC_DOT , LT(MOTIONLAYER, KC_SLASH ) , KC_RSHIFT ,

                       CTL_T(KC_NO) , ALT_T(KC_NO) , TG(NUMPAD) , KC_LOCK , LGUI(KC_M) ,

                       LGUI(KC_H) , LGUI(KC_L) ,
                       LGUI(KC_RIGHT) ,
                       LGUI(KC_LEFT) , LT(QWIMAMU , KC_TAB) , LT(NUMPAD, KC_ENTER)
                       ),

  [CAPSLAYER] = LAYOUT_ergodox(
                       // Left
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , LSFT( KC_Q ) , LSFT( KC_W ) , LSFT( KC_D ) , LSFT( KC_F ) , LSFT( KC_K ) , ___ ,
                       ___ , LSFT( KC_A ) , LSFT( KC_S ) , LSFT( KC_E ) , LSFT( KC_T ) , LSFT( KC_G ) ,
                       ___ ,  LSFT( KC_Z ) , LSFT(KC_X) ,  LSFT( KC_C )  , LSFT( KC_V ) , LSFT( KC_B ) , ___ ,
                       ___ , ___ , ___ , ___ , ___ ,

                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___ ,

                       // Right
                       ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                       ___ , LSFT( KC_J ) , LSFT( KC_U ) , LSFT( KC_R ) , LSFT( KC_L ) , KC_COLON , ___ ,
                       LSFT( KC_Y ) , LSFT( KC_N ) , LSFT( KC_I ) , LSFT( KC_O ) , LSFT( KC_H ) , ___ ,
                       ___ , LSFT( KC_P ) , LSFT( KC_M ) , LSFT( KC_COMMA ) , LSFT( KC_DOT ) , LSFT(KC_SLASH) , ___ ,
                       ___ , ___ , ___ , ___ , ___ ,

                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___
                       ),

 [TOPROWALT] = LAYOUT_ergodox(
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
                           ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ ,
                           ___ ,
                           ___ , ___ , ___

                       ),

  [TOPROWNUM] = LAYOUT_ergodox(
                            // Left
                            ___ , KC_1 , KC_2 , KC_3 , KC_4 , KC_5, ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ ,
                            ___ ,
                            ___ , ___ , ___ ,
                            // right
                            ___ , KC_6 , KC_7 , KC_8 , KC_9 , KC_0 , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
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
                      ___ , ___ ,
                      ___ ,
                      ___ , ___ , ___ ,
                      // right
                      ___ , ___ , KC_LABK , KC_RABK , KC_AMPR , KC_PIPE , ___ ,
                      WR_REDIR_2AND1 , KC_KP_PLUS , KC_7 , KC_8 , KC_9 , KC_SLASH , ___ ,
                      KC_MINUS , KC_4 , KC_5 , KC_6 , KC_DOT , ___ ,
                      ___ , KC_KP_ASTERISK , KC_1 , KC_2 , KC_3 , KC_0 , KC_ENTER ,
                      ___ , ___ , ___ , ___ ,  ___ ,
                      ___ , ___ ,
                      ___ ,
                      ___ , ___ , ___
                      ),

 [FLAYER] = LAYOUT_ergodox(
                           // Left

                           ___ , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,
                           ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ ,
                           ___ ,
                           ___ , ___ , ___ ,

                           // right

                           KC_F7 , KC_F8 , KC_F9 , KC_F10 , KC_F11 , KC_F12 , ___ ,
                           ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ , ___ , ___ , ___ ,
                           ___ , ___ ,
                           ___ ,
                           ___ , ___ , ___

                       ),

  // Symbols
  [SYMBOLS] = LAYOUT_ergodox(
                       // Left
                      ___ , KC_1 , KC_2 , KC_3 , KC_4 , KC_5, ___ ,
                      ___ , KC_PERC , KC_QUOTE , KC_LCBR , KC_RCBR ,  KC_CIRC , WR_ESCAPEDDOUBLEQUOTE ,
                      ___ , KC_AT , KC_DLR , KC_LEFT_PAREN , KC_RIGHT_PAREN, KC_KP_PLUS ,
                      ___ , KC_TILD , KC_GRAVE , KC_LBRACKET, KC_RBRACKET , KC_HASH , ___ ,
                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___ ,
                       // right
                      ___ , KC_6 , KC_7 , KC_8 , KC_9 , KC_0 , ___ ,
                      WR_ESCAPEDSINGLEQUOTE , LSFT(KC_SLASH) , KC_EXLM , KC_MINUS , LSFT( KC_QUOTE ) , KC_SCOLON , ___ ,
                      KC_COLN, KC_EQUAL , KC_PIPE , KC_AMPR , KC_BSLASH , WR_ESCAPEDRETURN ,
                       ___ , KC_KP_ASTERISK , KC_UNDS , KC_LABK , KC_RABK , ___ , ___ ,
                                              ___ , ___ , ___ , ___ , ___ ,

                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___
                       ),


  // Mouse and motion
  [MOTIONLAYER] = LAYOUT_ergodox(
                      // left
                      KC_ENTER , LCTL(KC_W) , LGUI(KC_O) , LGUI(KC_M) , LCS(KC_TAB) , LCTL(KC_TAB) , LCTL(KC_T) ,
                      KC_MS_BTN1 , ___ , KC_MS_WH_LEFT , KC_MS_UP , KC_MS_WH_RIGHT , KC_MS_WH_UP , KC_PGUP ,
                      ___ , ___ , KC_MS_LEFT , KC_MS_DOWN , KC_MS_RIGHT , KC_MS_WH_DOWN ,
                      ___ , LGUI(KC_LEFT) , LGUI(KC_H) , LGUI(KC_L) , LGUI(KC_RIGHT) , ___ , KC_PGDOWN ,
                      ___ , ___ , ___ , ___, ___,
                      ___ , ___ ,
                      KC_MS_BTN4 ,
                      KC_MS_BTN1 , KC_MS_BTN2 , KC_MS_BTN5 ,

                      // right
                      ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ , KC_HOME , ___ , KC_END , ___ , ___ ,
                      ___ , LCTL(KC_LEFT) , KC_UP , LCTL(KC_RIGHT) , ___ , ___ ,
                      ___ , ___ , KC_LEFT , KC_DOWN , KC_RIGHT , ___ , ___ ,
                      ___ , ___ , ___ , ___ , ___ ,
                      ___,  ___ ,
                      LCTL(KC_TAB) ,
                      LCS(KC_TAB) , ___ , ___
                      ),

  // Qwerty(hjkl)/vim, dynamic macro controls, tmux macros
  [QWIMAMU] = LAYOUT_ergodox(
                       // Left
                       DYN_REC_START1 , DYN_MACRO_PLAY1 , ___ , ___ , ___ , ___ , WR_SHEBANGS_BASH ,
                       DYN_REC_START2 , DYN_MACRO_PLAY2 , LCTL(KC_W) , LCS(KC_C) , LCS(KC_V) , ___ , ___ ,
                       DYN_REC_STOP , ___ , LCTL(KC_X) , LCTL(KC_C) , LCTL(KC_V) , LCTL(KC_Z) ,
                       TMUX_PSPLITH , ___ , TMUX_PFS , TMUX_COPYMODE , TMUX_PASTE , TMUX_PLAST , TMUX_PSPLITV ,

                       ___ , ___ , ___ , ___ , ___ ,

                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___ ,

                       // Right
                       TG(XPLANE) , ___ , ___ , WR_MD_TODO , ___ , WR_CODEFENCE , DOEXIT ,
                       VIM_CMD_MODE , ___ , ___ , WR_GREP , WR_LESS , ___ , VIM_NOH ,
                       VIM_BUFFER_PREV , VIM_BUFFER_PREV , KC_PIPE , ___ , KC_0 , KC_DLR ,
                       ___ , TMUX_WP , TMUX_WN , TMUX_WCREATE , ___ , WR_FLAGHELP,  ___ , //TD( TD_HELPFLAG ) ,

                       ___ , ___ , ___ , ___ , ___ ,
                       ___ , ___ ,
                       ___ ,
                       ___ , ___ , ___
                      ),

  [GOLANDLAYER] = LAYOUT_ergodox(
      // Left
                                 // move up, down
                                 LALT(KC_SCOLON) , CONALT(KC_ENTER) , ___ , LSFT(KC_F2) , KC_F2 , LALT(KC_R) , LCS(KC_F10) , // un-select last occurrence, start new line above, prev error, next error, move line up, run test
                                 LALT(KC_L) , LSFT(KC_ENTER) , LCTL(KC_4) , LSFT(KC_F6) , LSALT(KC_7) , LALT(KC_I) , MEH(KC_F) , // select next highlighted occurrence, start new line,  close tab, rename, find, move line down
                                 LCTL(KC_Y) , LCTL(KC_BSLASH) , ___ , ___ , LCS(KC_N) , LCS(KC_A) , // comment line, expand selection, select thru line start/end, open file, actions
                                 LCS(KC_9) , LCTL(KC_SLASH) , ___ , LSFT(KC_F7) , KC_F7 , LCS(KC_COMMA) , ___ , // back, delete line, (resolve conflicts)prev,next conflict, clone caret below
                                ___ , ___ , ___ , ___ , ___ ,
                                ___ , ___ ,
                                ___ ,
                                ___ , ___ , ___ ,
                                // right
                                 LALT(KC_7) , LALT(KC_1) , LALT(KC_2) , LALT(KC_3) , LALT(KC_4) , LALT(KC_5) , ___ ,
                                ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                                ___ , ___ , ___ , ___ , ___ , ___ ,
                                ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                                ___ , ___ , ___ , ___ , ___ ,
                                ___ , ___ ,
                                ___ ,
                                ___ , ___ , ___
                                 ),

  [MACROLAYER] = LAYOUT_ergodox(
                      // Left
                      ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ , ___ , WR_WORD_GOETHEREUM , ___ , ___ , ___ ,
                      ___ , ___ , ___ , WR_WORD_ETHEREUM, ___, WR_WORD_GITHUB_DOT_COM ,
                      ___ , KC_SLASH , ___ , WR_WORD_ETCLABSCORE, WR_WORD_MEOWSBITS , ___ , ___ ,
                      ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ ,
                      ___ ,
                      ___ , ___ , ___ ,
                      // right
                      ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ , ___ , WR_WORD_RETURN , ___ , ___ , ___ ,
                      ___ , ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ , ___ , ___ , ___ ,
                      ___ , ___ ,
                      ___ ,
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
                            ),

  [UNICODEL] = LAYOUT_ergodox(
                            // Left
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ , ___ , ___ , EMOJI_YAY , EMOJI_SHRUG ,
                            ___ , EMOJI_SMILE2 , EMOJI_EGGY2 , EMOJI_FACE1 , EMOJI_FACE2 , EMOJI_UHU , ___ ,
                            ___ , ___ , ___ , ___ , ___ ,
                            ___ , ___ ,
                            ___ ,
                            ___ , ___ , ___ ,
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
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
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

  /* case WR_COLONEQUALS: */
  /*   if (record->event.pressed) { */
  /*     SEND_STRING("2>&1"); */
  /*   } */
  /*   return false; */
  /*   break; */

  case WR_REDIR_2AND1:
    if (record->event.pressed) {
      SEND_STRING("2>&1");
    }
    return false;
    break;

  case WR_REDIR_STDERR:
    if (record->event.pressed) {
      SEND_STRING("2>");
    }
    return false;
    break;

  case WR_REDIR_STDOUT:
    if (record->event.pressed) {
      SEND_STRING("1>");
    }
    return false;
    break;

  case WR_DOUBLE_LBRACKET:
    if (record->event.pressed) {
      SEND_STRING("[[");
    }
    return false;
    break;

  case WR_DOUBLE_RBRACKET:
    if (record->event.pressed) {
      SEND_STRING("]]");
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

  case WR_ESCAPEDSINGLEQUOTE:
    if (record->event.pressed) {
      SEND_STRING("\\\'");
    }
    return false;
    break;

  case WR_SHEBANGS_BASH:
    if (record->event.pressed) {
      SEND_STRING("#!/usr/bin/env bash");
    }
    return false;
    break;

  case WR_FLAGHELP:
    if (record->event.pressed) {
      SEND_STRING("--help");
    }
    return false;
    break;

  case WR_FLAGHELPLESS:
    if (record->event.pressed) {
      SEND_STRING("--help | less");
    }
    return false;
    break;

  case WR_PIPE_LESS:
    if (record->event.pressed) {
      SEND_STRING("| less ");
    }
    return false;
    break;

  case WR_LESS:
    if (record->event.pressed) {
      SEND_STRING("less ");
    }
    return false;
    break;

  case WR_GREP:
    if (record->event.pressed) {
      SEND_STRING("grep ");
    }
    return false;
    break;

  case WR_SLASHSLASH:
    if (record->event.pressed) {
      SEND_STRING("// ");
    }
    return false;
    break;

  case WR_MD_TODO:
    if (record->event.pressed) {
      SEND_STRING("- [ ] ");
    }
    return false;
    break;

  case WR_IFS_EQ:
    if (record->event.pressed) {
      SEND_STRING("IFS=");
    }
    return false;
    break;

  case WR_WORD_ETHEREUM:
    if (record->event.pressed) {
      SEND_STRING("ethereum");
    }
    return false;
    break;

  case WR_WORD_GOETHEREUM:
    if (record->event.pressed) {
      SEND_STRING("go-ethereum");
    }
    return false;
    break;

  case WR_WORD_ETCLABSCORE:
    if (record->event.pressed) {
      SEND_STRING("etclabscore");
    }
    return false;
    break;

  case WR_WORD_GITHUB_DOT_COM:
    if (record->event.pressed) {
      SEND_STRING("github.com/");
    }
    return false;
    break;

  case WR_WORD_MEOWSBITS:
    if (record->event.pressed) {
      SEND_STRING("meowsbits");
    }
    return false;
    break;

  case WR_WORD_RETURN:
    if (record->event.pressed) {
      SEND_STRING("return ");
    }
    return false;
    break;

  case WR_CD_DEV_ETCLABSCORE:
    if (record->event.pressed) {
      SEND_STRING("cd ~/dev/etclabscore");
    }
    return false;
    break;

  case WR_BUILD_BIN_GETH:
    if (record->event.pressed) {
      SEND_STRING("./build/bin/geth");
    }
    return false;
    break;

  case WR_GETH:
    if (record->event.pressed) {
      SEND_STRING("geth");
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

  case VIM_NOH:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP( X_ESCAPE )":noh"SS_TAP(X_ENTER));
    }
    return false;
    break;

  case VIM_BUFFER_PREV:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP( X_ESCAPE )":bprev"SS_TAP(X_ENTER));
    }
    return false;
    break;

  case VIM_BUFFER_NEXT:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP( X_ESCAPE )":bnext"SS_TAP(X_ENTER));
    }
    return false;
    break;

  case WORD_P2P:
    if (record->event.pressed) {
      SEND_STRING("p2p");
    }
    return false;
    break;

  case WORD_BECAUSE:
    if (record->event.pressed) {
      SEND_STRING("because ");
    }
    return false;
    break;

  case WORD_WOULD:
    if (record->event.pressed) {
      SEND_STRING("would ");
    }
    return false;
    break;

  case WORD_SHOULD:
    if (record->event.pressed) {
      SEND_STRING("should ");
    }
    return false;
    break;

  case WORD_COULD:
    if (record->event.pressed) {
      SEND_STRING("could ");
    }
    return false;
    break;

  case WORD_ABOUT:
    if (record->event.pressed) {
      SEND_STRING("about ");
    }
    return false;
    break;

  case SPACEMACS_WINDOW_LEFT:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE)SS_TAP(X_SPACE)"wl");
    }
    return false;
    break;

  case SPACEMACS_NEOTREE_TOGGLE:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE)" ft");
    }
    return false;
    break;

  case SPACEMACS_WINDOW_RIGHT:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE)SS_TAP(X_SPACE)"wh");
    }
    return false;
    break;

  case SPACEMACS_WINDOW_UP:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE)SS_TAP(X_SPACE)"wk");
    }
    return false;
    break;

  case SPACEMACS_WINDOW_DOWN:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE)SS_TAP(X_SPACE)"wj");
    }
    return false;
    break;

  /* case LOCK_SHIFT: */
  /*   if (record->event.pressed) { */
  /*     tap_code(X_LOCK); */
  /*     tap_code(X_LSHIFT); */
  /*   } */
  /*   return false; */
  /*   break; */

#ifdef UNICODE_ENABLE
  case EMOJI_UHU:
    if (record->event.pressed) {
      send_unicode_hex_string("2299 FE4F 2299");
    }
    return false;
    break;

  case EMOJI_FACE2:
    if (record->event.pressed) {
      send_unicode_hex_string("0028 2022 005F 2022 0029");
    }
    return false;
    break;

  case EMOJI_FACE1:
    if (record->event.pressed) {
      send_unicode_hex_string("0028 002D 005F 002D 0029");
    }
    return false;
    break;

  case EMOJI_EGGY2:
    if (record->event.pressed) {
      send_unicode_hex_string("30CE 0028 0020 309C 002D 309C 30CE 0029");
    }
    return false;
    break;

  case EMOJI_SMILE2:
    if (record->event.pressed) {
      send_unicode_hex_string("0028 0298 203F 0298 0029");
    }
    return false;
    break;

  case EMOJI_SHRUG: // // ¯\_(ツ)_/¯
    if (record->event.pressed) {
      send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
    }
    return false;
    break;
#endif

  case EMOJI_YAY:
    if (record->event.pressed) {
      SEND_STRING ("\\o/");
    }
    return false;
    break;

  }

  return true;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CURLYBRACKET] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TD_PAREN] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_PAREN, KC_RIGHT_PAREN),
    [TD_BRACKET] = ACTION_TAP_DANCE_DOUBLE(KC_LBRACKET, KC_RBRACKET),
    [TD_QUOTE_COUNTERINTUITIVE] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_QUOTE), KC_QUOTE),
    [TD_HYPHEN_EQUALS] = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, KC_EQUAL),
    [TD_HELPFLAG] = ACTION_TAP_DANCE_DOUBLE(WR_FLAGHELP, WR_FLAGHELPLESS)
};

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
