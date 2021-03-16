#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define ___ KC_TRANSPARENT

#define LCS(code) LCTL(LSFT(code))
#define LSALT(code) LALT(LSFT(code))
#define CONALT(code) LCTL(LALT(code))
#define CTLGUI(code) LCTL(LGUI(code))
#define LGSFT(code) LGUI(LSFT(code))

// https://www.reddit.com/r/olkb/comments/72u8ou/qmk_mouse_keys_rock/

enum {
    BASE = 0,  // Norman layout
    CAPSLAYER,
    NUMPAD,
    SYMBOLS,
    MOTIONLAYER,
    QWIMAMU,  // qwerty/+vim: hjkl and navigation friends on right hand, with F- keys in top row
    GOLANDLAYER,
    MACROLAYER,  // words, and stuff
    FLAYER,
    UNICODEL,
    DEADQWERTY,
};

// TAP DANCES
enum {
    X_CTL = 0,

    TD_CURLYBRACKET = 0,
    TD_PAREN,
    TD_BRACKET,
    TD_QUOTE_COUNTERINTUITIVE,
    TD_HYPHEN_EQUALS,
    TD_HELPFLAG,

    TD_LGUI_DOUBLEQUOTE,

    TD_QUESTION_TOPROWNUM,
    TD_TAB_TMUXQ,
    TD_LEADER_TMUXQ,
    TD_DQUOTE_MOTION,
    TD_TODO_DONE,
    TD_LABK_COMMA,
    TD_RABK_DOT,
    TD_BASH_INTERVAR,

    TD_TMUX2,  // shift + motion, good for selecting batches of text
    TD_ALT_QUESTION,
    TD_COPY_PASTE,

    // Tap dance enums
    TD_ALT_UNI,
    TD_SHIFT_CAP,
    ONEORMO_SYMBOLS,
    TD_FANCYAWESOMEQUOTE,
    AWESOME_TAG_FORWARD_BACK,
    AWESOME_TAG_NEXT_SCREEN_OR_APP,
    /* SOME_OTHER_DANCE */

    TD_TOBASE_CLEAN,
    TD_AWESOME_SELECT_TAG,

    TD_MOUSE_BACKFORWARD,
    TD_FANCY_CODEFENCE,
    TD_LEFT_BLUE_THUMB,
    TD_RIGHT_BLUE_THUMB,
    TD_TOP_RIGHT_0,
};

/* ------------------------------------------------------------------ */
// https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance

typedef struct {
    bool is_press_action;
    int  state;
} tap;

enum {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5,  // send two single taps
    TRIPLE_TAP        = 6,
    TRIPLE_HOLD       = 7,
};

int cur_dance(qk_tap_dance_state_t *state);

// for the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);

/* ------------------------------------------------------------------ */

enum unicode_names {
    UNIC_COPYRIGHT,
    UNIC_REGISTERED,

    UNIC_KEYBOARD,
    UNIC_OPTION,
    UNIC_COMMAND,

    UNIC_MDASH,
    UNIC_PILCROW,
    UNIC_OBELISM,
    UNIC_BLOCK,
    UNIC_STACK,

    UNIC_ZAP,
    UNIC_TOOLS,

    UNIC_CHECKMARK,
    UNIC_THUMPSUP,

    UNIC_THINKING,
    UNIC_TIMERCLOCK,

    SNEK,
    UNIC_SQUIRREL,
    UNIC_CAT,

    UNIC_OMICRON,

    UNIC_SUBSET_OF,
    UNIC_SUPERSET_OF,
};

const uint32_t PROGMEM unicode_map[] = {
    [UNIC_COPYRIGHT]  = 0x00A9,  // ©
    [UNIC_REGISTERED] = 0x00AE,  // ®

    [UNIC_KEYBOARD] = 0x2328,  // ⌨
    [UNIC_OPTION]   = 0x2325,  // ⌥
    [UNIC_COMMAND]  = 0x2318,  // ⌘

    [UNIC_MDASH]   = 0x2014,  // —
    [UNIC_PILCROW] = 0x00B6,  // ⁋
    [UNIC_OBELISM] = 0x205B,  // ⁛
    [UNIC_BLOCK]   = 0x2588,  // █
    [UNIC_STACK]   = 0x26C1,  // ⛁

    [UNIC_ZAP]   = 0x26A1,   // :zap:
    [UNIC_TOOLS] = 0x1F6E1,  // :tools:

    [UNIC_CHECKMARK] = 0x2705,   // :white_checkmark:
    [UNIC_THUMPSUP]  = 0x1F44D,  // :+1:

    [UNIC_THINKING]   = 0x1F914,  // :thought:
    [UNIC_TIMERCLOCK] = 0x23F2,   // :timer_clock:

    [SNEK]          = 0x1F40D,  // 🐍
    [UNIC_SQUIRREL] = 0x1F43F,  // :squirrel:
    [UNIC_CAT]      = 0x1F408,  // :cat:

    [UNIC_OMICRON] = 0x03BF,  // omicron o

    [UNIC_SUBSET_OF] = 0x2282,  [UNIC_SUPERSET_OF] = 0x2283,

};

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,  // can always be here
    EPRM,
    RGB_SLD,
    // Mine/

    DOEXIT,  // type 'exit' and tap enter

    TMUX_COPYMODE,
    TMUX_PASTE,
    TMUX_LEADER,
    TMUX_LEADER2,

    TMUX_WN,       // window next
    TMUX_WP,       // window previous
    TMUX_WCREATE,  // create windw
    TMUX_WKILL,    // kill window

    TMUX_PANE_SELECT,
    TMUX_PANE_SELECT2,
    TMUX_PFS,      // pane fullscreen == leader,z
    TMUX_PLAST,    // pane last active
    TMUX_PSPLITH,  // pane split horizontally
    TMUX_PSPLITV,  // pane split vertically

    TMUX_PANE_UP,
    TMUX_PANE_DOWN,
    TMUX_PANE_RIGHT,
    TMUX_PANE_LEFT,

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
    VIM_EXECUTE_FILE,

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
    WR_HTTP,
    WR_HTTPS,
    WR_PROTO_COLON_SLASHSLASH,
    WR_LOCALHOST,

    WR_FLAGHELP,
    WR_FLAGHELPLESS,

    WR_COLONEQUALS,
    WR_NOTEQUALS,
    WR_EQUALSEQUALS,

    WR_MD_TODO,

    WR_WORD_ETHEREUM,
    WR_WORD_GOETHEREUM,
    WR_WORD_OPENETHEREUM,
    WR_WORD_MULTIGETH_DASHED,
    WR_WORD_COREGETH_DASHED,
    WR_WORD_EIP,
    WR_WORD_ECIP,
    WR_WORD_GITHUB_DOT_COM,
    WR_WORD_ETCLABSCORE,
    WR_WORD_OPENRPC,
    WR_WORD_OPEN_RPC,
    WR_CD_DEV_ETCLABSCORE,
    WR_WORD_ROTBLAUER,
    WR_WORD_MEOWSBITS,
    WR_WORD_RETURN,
    WR_BUILD_BIN_GETH,
    WR_GETH,
    WR_PIPE_LESS,
    WR_LESS,
    WR_GREP,
    WR_WORD_SYSTEM,
    WR_WORD_ETCSYSTEMDSYSTEM,
    WR_WORD_JOURNALCTL,
    WR_WORD_MASTER,
    WR_WORD_MAKE,
    WR_WORD_GETH,
    WR_WORD_LINT,

    WR_WORD_GO_IFERRNN,

    WR_GOSRC_ETHEREUM_GOETHEREUM,

    // Bash syntax stuff
    /* BASH_INTERVAR, */
    WR_BASH_INTERVAR,
    WR_BASH_INTERFN,

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
    WR_WORD_P2P,

    SPACEMACS_WINDOW_LEFT,
    SPACEMACS_WINDOW_RIGHT,
    SPACEMACS_WINDOW_UP,
    SPACEMACS_WINDOW_DOWN,
    SPACEMACS_NEOTREE_TOGGLE,

    LOCK_SHIFT,

    SYMBOLS_ONE_OR_HOLD,

    DYNAMIC_MACRO_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Norman and friends
    [BASE] = LAYOUT_ergodox(
        // Left
        // still not happy about top left. slash gets hit twice too many times. tab too.
        TD(TD_LEADER_TMUXQ), KC_UP, LT(MACROLAYER, KC_0), KC_DLR, KC_KP_ASTERISK, KC_DOWN, CTLGUI(KC_SPACE) ,  // ___ , // LCTL(KC_SLASH) , // CTLGUI(KC_K) , // LT( TOPROWALT, KC_TAB )

        TD(AWESOME_TAG_FORWARD_BACK), LT(FLAYER, KC_Q), KC_W, KC_D, KC_F, KC_K, MT(MOD_MEH, KC_ENTER),        // /
        LT(SYMBOLS, KC_ESCAPE), LT(MOTIONLAYER, KC_A), KC_S, KC_E, KC_T, KC_G,                                // /
        TD(TD_SHIFT_CAP), LT(QWIMAMU, KC_Z), LT(NUMPAD, KC_X), ALT_T(KC_C), KC_V, LCTL_T(KC_B), TD(TD_LEFT_BLUE_THUMB), // LSFT(KC_QUOTE),  // TD(TD_COPY_PASTE)  // TD_TMUX2// includes TMUX_LEADER2 as the single_tap

        TD(TD_MOUSE_BACKFORWARD), ___, ___, MT(MOD_LALT, KC_SLASH), MT(MOD_LGUI, KC_TAB),  // TD(TD_ALT_QUESTION), TD(TD_LGUI_DOUBLEQUOTE), // MT(MOD_LGUI, KC_TAB),  // TD(TD_ALT_UNI)

        /*  */
        LT(GOLANDLAYER, KC_DELETE), KC_R,           //  TG(TOPROWNUM) , // hold for motion layer is nice for left-handed scrolling; KC_R is nice for reloading stuff sometimes (ie flutter)
        KC_INSERT,                                 // KC_INSERT , // LCTL(KC_TAB) ,
        SFT_T(KC_SPACE), KC_BSPACE, TD(TD_TMUX2),  // //  LCS(KC_TAB) , // browser tab left

        // Right
        TD(TD_TOBASE_CLEAN), LSFT(KC_SLASH), KC_QUOTE, LT(MACROLAYER, KC_MINUS), KC_UNDS, KC_GRAVE, TD(TD_TOP_RIGHT_0), // LGUI(KC_ENTER),      // LCS(KC_TAB) , LCTL(KC_TAB)
        KC_BSPACE, KC_J, KC_U, KC_R, KC_L, LT(FLAYER, KC_SCOLON), TD(AWESOME_TAG_NEXT_SCREEN_OR_APP),           // CTLGUI(KC_K) , //LGUI(KC_RIGHT) , // OSM(MOD_LSFT) , // LT(DELAYER, KC_QUOTE) , // MT(MOD_HYPR, KC_SCOLON )
        KC_Y, LT(GOLANDLAYER, KC_N), KC_I, KC_O, KC_H, KC_LCTRL,                                     // MO(SYMBOLS),// MO(SYMBOLS), // TD(ONEORMO_SYMBOLS), // MO(SYMBOLS) , // b/c i use symbols a lot, no 200ms wait //
        TD(TD_RIGHT_BLUE_THUMB), LGUI_T(KC_P), KC_M, ALT_T(KC_COMMA), KC_DOT, LT(MOTIONLAYER, KC_SLASH), TD(TD_SHIFT_CAP), // LSFT(KC_SLASH)   // , TD(TD_SHIFT_CAP), // OSM(MOD_LSFT) , // KC_RSHIFT ,

        TD(ONEORMO_SYMBOLS), LSFT(KC_SLASH), TG(NUMPAD), TG(MOTIONLAYER), OSL(UNICODEL),  // CONALT(KC_0) , // mute/unmute microphone */ // KC_LEAD

        /* */
        LGUI(KC_Y) , LGUI(KC_Z),                                  // /
        ___ ,                                              // /
        ___ , LT(QWIMAMU, KC_TAB), LT(NUMPAD, KC_ENTER)),  //

    [CAPSLAYER] = LAYOUT_ergodox(
        // Left
        ___, ___, ___, ___, ___, ___, ___,                                     //
        ___, LSFT(KC_Q), LSFT(KC_W), LSFT(KC_D), LSFT(KC_F), LSFT(KC_K), ___,  //
        ___, LSFT(KC_A), LSFT(KC_S), LSFT(KC_E), LSFT(KC_T), LSFT(KC_G),       //
        ___, LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_V), LSFT(KC_B), ___,  //
        ___, ___, ___, ___, ___,                                               //

        ___, ___, ___, ___, ___, ___,  //

        // Right
        ___, ___, ___, ___, ___, ___, ___,                                //
        ___, LSFT(KC_J), LSFT(KC_U), LSFT(KC_R), LSFT(KC_L), ___, ___,    //
        LSFT(KC_Y), LSFT(KC_N), LSFT(KC_I), LSFT(KC_O), LSFT(KC_H), ___,  //
        ___, LSFT(KC_P), LSFT(KC_M), ___, ___, ___, ___,                  //
        ___, ___, ___, ___, ___,                                          //

        ___, ___, ___, ___, ___, ___  //

        ),

    // Numpad
    [NUMPAD] = LAYOUT_ergodox(
        // Left
        ___, KC_0, KC_1, KC_2, KC_3, KC_4, ___,                 // /
        ___, ___, LSFT(KC_QUOTE), KC_LCBR, KC_RCBR, ___, ___,              // /
        ___, ___, KC_DLR, KC_LEFT_PAREN, KC_RIGHT_PAREN, ___,   // /
        ___, ___, ___, KC_LBRACKET, KC_RBRACKET, KC_HASH, ___,  // /
        ___, ___, ___, ___, ___,                                // /
        ___, ___,                                               // /
        ___,                                                    // /
        ___, ___, ___,                                          // /

        /*

         */
        // right
        ___, KC_PERC, KC_EQUAL, KC_MINUS, KC_UNDS, ___, ___,  // /
        ___, KC_COLN, KC_7, KC_8, KC_9, KC_SLASH, ___,            // /
        KC_KP_PLUS, KC_4, KC_5, KC_6, KC_0, KC_ENTER,             // /
        ___, KC_KP_ASTERISK, KC_1, KC_2, KC_3, KC_DOT, KC_COMMA,  // /
        ___, ___, ___, ___, ___,                                  // /
        ___, ___,                                                 // /
        ___,                                                      // /
        ___, ___, ___                                             // /
        ),

    // Symbols
    [SYMBOLS] = LAYOUT_ergodox(
        // Left
        ___, KC_1, KC_2, KC_3, KC_4, KC_5, ___,  // /
        /* ___ , KC_0 , KC_1 , KC_2 , KC_3 , KC_4 , ___ , */
        KC_COMMA, KC_PERC, KC_QUOTE, KC_LCBR, KC_RCBR, KC_CIRC, ___,                    // WR_ESCAPEDDOUBLEQUOTE
        ___, KC_AT, KC_DLR, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_KP_PLUS,             // /
        ___, KC_TILD, KC_GRAVE, KC_LBRACKET, KC_RBRACKET, KC_HASH, TO(CAPSLAYER),  // /
        ___, ___, ___, ___, ___,                                                   // /

        ___, ___,  // /
        ___,               // /
        ___, ___, ___,     // /

        // right
        ___, KC_6, KC_7, KC_8, KC_9, KC_0, ___,  // /
        /* ___ , KC_5 , KC_6 , KC_7 , KC_8 , KC_9 , ___ , */
        KC_DOT, LSFT(KC_SLASH), KC_EXLM, KC_MINUS, LSFT(KC_QUOTE), KC_SCOLON, KC_DOT,  // /
        KC_COLN, KC_EQUAL, KC_PIPE, KC_AMPR, KC_BSLASH, ___,                        // < WR_ESCAPEDRETURN ,
        /* ___ , KC_KP_ASTERISK , KC_UNDS , TD( TD_LABK_COMMA ) , TD( TD_RABK_DOT ) , ___ , ___ , // */
        ___, KC_KP_ASTERISK, KC_UNDS, KC_LABK, KC_RABK, ___, ___,  //
        ___, ___, ___, ___, ___,                                   // /

        ___, ___,  // /
        ___,               // /
        ___, ___, ___      // /
        ),

    // Mouse and motion
    [MOTIONLAYER] = LAYOUT_ergodox(
        /* // Left */
        ___, ___, LCS(KC_PGUP), LCS(KC_TAB), LCTL(KC_TAB), LCS(KC_PGDOWN), ___, ___, LCTL(KC_W), KC_MS_WH_UP, KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, KC_PGUP,  // /
        ___, ___, KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,                                                                                            // /
                                                                                                                                                                 //        ___, ___, ___, CTLGUI(KC_SPACE), LGUI(KC_M), KC_LSHIFT, KC_PGDOWN,               // floating, maximized, ...
        ___, ___, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_LSHIFT, KC_PGDOWN,                                                                                      // floating, maximized, ...
        ___, ___, ___, ___, ___,                                                                                                                                 // /
        /* LGUI(KC_H) , LGUI(KC_L) , */
        KC_SLASH, ___,                          // /
        LGUI(KC_RIGHT),                         // /
        KC_MS_BTN1, KC_MS_BTN2, LGUI(KC_LEFT),  // /  // KC_ENTER

        // right
        ___, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), LCS(KC_1),  // /
        LCTL(KC_X), ___, KC_HOME, ___, KC_END, ___, LCS(KC_2),                       // /
        ___, LCTL(KC_LEFT), KC_UP, LCTL(KC_RIGHT), ___, LCTL(KC_V),                  // /
        LCTL(KC_C), ___, KC_LEFT, KC_DOWN, KC_RIGHT, ___, ___,                       // /
        ___, ___, ___, ___, ___,                                                     // /
        ___, ___,                                                                    // /
        ___,                                                                         // /
        ___, ___, ___                                                                // /
        ),

    // Qwerty(hjkl)/vim, dynamic macro controls, tmux macros
    [QWIMAMU] = LAYOUT_ergodox(
        // Left
        DYN_REC_STOP, ___, ___, ___, ___, ___, WR_SHEBANGS_BASH,                                   // /
        DYN_REC_START1, DYN_MACRO_PLAY1, LCTL(KC_W), LCS(KC_C), LCS(KC_V), ___, VIM_EXECUTE_FILE,  // /
        DYN_REC_START2, DYN_MACRO_PLAY2, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_Z),           // /
        TMUX_PSPLITH, ___, TMUX_PFS, TMUX_COPYMODE, TMUX_PASTE, TMUX_PLAST, TMUX_PSPLITV,          // /
        ___, ___, ___, ___, ___,                                                                   // /
        TMUX_PANE_LEFT, TMUX_PANE_RIGHT,                                                           // /
        TMUX_PANE_UP,                                                                              // /
        ___, ___, TMUX_PANE_DOWN,                                                                  // /

        // Right
        TG(DEADQWERTY), ___, ___, TD(TD_TODO_DONE), ___, TD(TD_FANCY_CODEFENCE), DOEXIT,  // /                                                                                                                          // TG(XPLANE)
        LGSFT(KC_C), ___, ___, WR_GREP, WR_LESS, ___, VIM_NOH,                            // /
        VIM_BUFFER_PREV, VIM_BUFFER_NEXT, KC_PIPE, ___, KC_0, KC_DLR,                     // /
        ___, TMUX_WP, TMUX_WN, TMUX_WCREATE, ___, TD(TD_HELPFLAG), ___,                   // TD( TD_HELPFLAG ) , // WR_FLAGHELP,
        ___, ___, ___, ___, CONALT(KC_0),                                                 // mute/unmute system microphone
        ___, ___,                                                                         // /
        ___,                                                                              // /
        ___, ___, ___                                                                     // /
        ),

    //
    // Find word at caret : ctrl+3
    // Find next/move to next occurrence : F3
    // Find prev/move to prev occurrence: Shift+F3
    // Select all occurrences: Ctrl+Alt+L
    // Select navigation bar: Alt+Home
    // ---
    // Add selection for next occurrence: Alt+L
    // Unselect next occurrence: Alt+;

    [GOLANDLAYER] = LAYOUT_ergodox(
        // Left
        // move up, down
        LALT(KC_SCOLON), CONALT(KC_ENTER), LALT(KC_3), LSFT(KC_F2), KC_F2, LALT(KC_R), LALT(KC_HOME),  // un-select last occurrence, start new line above, toggle Find window, prev error, next error, move line up, navigator focus
        LALT(KC_L), LSFT(KC_ENTER), LCTL(KC_4), LSFT(KC_F6), LSALT(KC_7), LALT(KC_I), LALT(KC_1),      // select next highlighted occurrence, start new line,  close tab, rename, find, move line down, project foucs
        LCTL(KC_Y), LCTL(KC_BSLASH), LCS(KC_9), LCS(KC_0), LCS(KC_N), LCS(KC_A),                       // delete line, expand selection, back, forward, open file, actions
        CONALT(KC_B), LCTL(KC_SLASH), ___, LSFT(KC_F7), KC_F7, LCS(KC_COMMA), LCS(KC_F10),             // _go to implementations, comment line, (resolve conflicts)prev,next conflict, clone caret below, run test
        ___, ___, ___, ___, ___,

        ___, LALT(KC_1),          // toggle Navigate pane
        LALT(KC_3),               // toggle Find pane
        LCS(KC_SPACE), ___, ___,  // autocomplete types

        // right
        LALT(KC_2), LALT(KC_1), LALT(KC_7), LALT(KC_3), LALT(KC_4), LALT(KC_5), LALT(KC_9),         // ... , focus git view
        LCS(KC_G), ___, ___, LSFT(KC_F3), KC_F3, LCTL(KC_5), LALT(KC_F12),                          // Toggle minimap, prev / next occurrence (word at caret), rerun last, focus console view
        ___, ___, ___, MEH(KC_RBRACKET), MEH(KC_LBRACKET), LCTL(KC_1),                              // cursor to pane left / right, show error description
        MEH(KC_F), MEH(KC_PGUP), ___, LCA(KC_LBRACKET), LCA(KC_RBRACKET), MEH(KC_PGDN), MEH(KC_Z),  // gofmt,  shift pane left, streth pane l/r, shift pan right, toggle distraction free

        // LCA(KC_LBRACKET), LCA(KC_RBRACKET) // Stretch panes left / right
        ___, ___, ___, ___, ___,  //
        ___, ___,                 // /
        ___,                      // /
        ___, LCTL(KC_3), ___      // /
        ),

    [MACROLAYER] = LAYOUT_ergodox(
        // Left
        ___, WR_GOSRC_ETHEREUM_GOETHEREUM, WR_BUILD_BIN_GETH, ___, ___, ___, ___,                   // /
        ___, ___, WR_WORD_ETCSYSTEMDSYSTEM, WR_WORD_GOETHEREUM, WR_WORD_COREGETH_DASHED, ___, ___,  // /
        ___, ___, WR_WORD_SYSTEM, WR_WORD_ETHEREUM, ___, WR_WORD_GITHUB_DOT_COM,                    // /
        ___, KC_SLASH, ___, WR_WORD_ETCLABSCORE, WR_WORD_MEOWSBITS, KC_DOT, ___,                    // /
        ___, ___, ___, ___, ___,                                                                    // /
        ___, ___,                                                                                   // /
        ___,                                                                                        // /
        ___, ___, ___,                                                                              // /

        /*

         */

        // right
        ___, ___, ___, ___, ___, ___, ___,                                    // /
        ___, WR_WORD_JOURNALCTL, ___, WR_WORD_ROTBLAUER, ___, WR_HTTPS, ___,  // WR_PROTO_COLON_SLASHSLASH
        ___, ___, ___, ___, WR_HTTP, ___,                                     // /
        ___, WR_WORD_P2P, WR_WORD_MASTER, ___, WR_REDIR_2AND1, ___, ___,      // /
        ___, ___, ___, ___, ___,                                              // /
        ___, ___,                                                             // /
        ___,                                                                  // /
        ___, ___, ___                                                         // /
        ),

    [FLAYER] = LAYOUT_ergodox(
        // Left
        ___, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,  // /
        ___, ___, ___, ___, ___, ___, ___,              // /
        ___, ___, ___, ___, ___, ___,                   // /
        ___, ___, ___, ___, ___, ___, ___,              // /
        ___, ___, ___, ___, ___,                        // /
        ___, ___,                                       // /
        ___,                                            // /
        ___, ___, ___,                                  // /

        // right
        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, ___,  // /
        ___, ___, ___, ___, ___, ___, ___,                 // /
        ___, ___, ___, ___, ___, ___,                      // /
        ___, ___, ___, ___, ___, ___, ___,                 // /
        ___, ___, ___, ___, ___,                           // /
        ___, ___,                                          // /
        ___,                                               // /
        ___, ___, ___                                      // /
        ),

    [UNICODEL] = LAYOUT_ergodox(
        // Left
        X(SNEK), ___, ___, ___, ___, X(UNIC_SUPERSET_OF), X(UNIC_CHECKMARK),  // /
        ___, ___, ___, ___, ___, X(UNIC_SUBSET_OF), X(UNIC_THUMPSUP),         // /
        ___, ___, X(UNIC_STACK), ___, ___, ___,                               // /
        ___, X(UNIC_ZAP), ___, X(UNIC_COPYRIGHT), ___, X(UNIC_BLOCK), ___,    // /
        ___, ___, ___, ___, ___,                                              // /
        ___, ___,                                                             // /
        ___,                                                                  // /
        ___, ___, ___,                                                        // /
        // right
        ___, ___, ___, X(UNIC_MDASH), ___, ___, X(UNIC_SQUIRREL),                   // /
        ___, ___, ___, X(UNIC_REGISTERED), ___, ___, X(UNIC_CAT),                   // /
        ___, ___, ___, X(UNIC_OMICRON), ___, ___,                                   // /
        ___, X(UNIC_PILCROW), ___, ___, ___, X(UNIC_THINKING), X(UNIC_TIMERCLOCK),  // /
        ___, X(UNIC_OPTION), ___, ___, X(UNIC_KEYBOARD),                            // /
        ___, ___,                                                                   // /
        ___,                                                                        // /
        ___, ___, ___                                                               // /
        ),

    [DEADQWERTY] = LAYOUT_ergodox(KC_ESC, KC_V, KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT, KC_M,

                                  // orig: KC_TAB,          KC_Q,        KC_W,          KC_E,    KC_R,    KC_T,    ___,
                                  KC_H, KC_B, KC_Q, KC_W, KC_E, KC_R, KC_ENTER,
                                  // orig: KC_CAPS,         KC_A,        KC_S,          KC_D,    KC_F,    KC_G,
                                  KC_G, KC_SPACE, KC_A, KC_S, KC_D, KC_F,
                                  // orig: KC_LSHIFT,         CTL_T(KC_Z), KC_X,          KC_C,    KC_V,    KC_B,    KC_LCTL ,
                                  ___, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_E, KC_R,

                                  KC_BSPACE, ___, ___, ___, KC_CAPS,                     // /
                                  KC_F, KC_RBRACKET, KC_LBRACKET, KC_TAB, KC_LCTL, ___,  // /

                                  // right hand
                                  ___, KC_6, KC_7, KC_8, KC_9, KC_0, ___,      // /
                                  ___, KC_Y, KC_U, KC_I, KC_O, KC_P, ___,      // /
                                  KC_H, KC_J, KC_K, KC_L, KC_SCLN, ___,        // /
                                  ___, KC_N, KC_M, KC_COMM, KC_DOT, ___, ___,  // /

                                  ___, ___, ___, ___, ___,           //
                                  ___, ___, ___, ___, ___, KC_ENTER  // /
                                  )                                  //
};

LEADER_EXTERNS();

void leader_start(void) {
    // sequence started
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
}

void leader_end(void) {
    // sequence ended (no success/failuer detection)
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        // G: git
        SEQ_TWO_KEYS(KC_G, KC_P) { SEND_STRING("git push "); }
        SEQ_THREE_KEYS(KC_G, KC_P, KC_T) { SEND_STRING("git push --tags "); }
        SEQ_TWO_KEYS(KC_G, KC_L) { SEND_STRING("git pull "); }
        SEQ_THREE_KEYS(KC_G, KC_C, KC_A) { SEND_STRING("git commit -S --amend "); }
        SEQ_THREE_KEYS(KC_G, KC_R, KC_I) { SEND_STRING("git rebase -S -i "); }
        SEQ_THREE_KEYS(KC_G, KC_S, KC_S) { SEND_STRING("git stash save "); }
        SEQ_THREE_KEYS(KC_G, KC_S, KC_P) { SEND_STRING("git stash pop "); }
    }
}

bool                   suspended    = false;
const uint16_t PROGMEM fn_actions[] = {[1] = ACTION_LAYER_TAP_TOGGLE(1)};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case 0:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            break;
    }
    return MACRO_NONE;
};

static uint16_t key_timer;
bool            process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* if (!process_record_dynamic_macro(keycode, record)) { */
    /*   return false; */
    /* } */
    switch (keycode) {
            // dynamically generate these.
        case SYMBOLS_ONE_OR_HOLD:
            if (record->event.pressed) {
                key_timer = timer_read();
                layer_on(SYMBOLS);
            } else {
                layer_off(SYMBOLS);
                if (timer_elapsed(key_timer) < 150) {
                    set_oneshot_layer(SYMBOLS, ONESHOT_START);
                    clear_oneshot_layer_state(ONESHOT_PRESSED);
                }
            }
            return false;
            break;
        case EPRM:
            if (record->event.pressed) {
                eeconfig_init();
            }
            return false;
            break;

        case TMUX_COPYMODE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "[");
            }
            // else is event released
            return false;
            break;

        case TMUX_PASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "]");
            }
            return false;
            break;

        case TMUX_LEADER:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b"));
            }
            return false;
            break;

        case TMUX_LEADER2:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") SS_LCTRL("b"));
            }
            return false;
            break;

        case TMUX_WN:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "n");
            }
            return false;
            break;

        case TMUX_WP:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "p");
            }
            return false;
            break;

        case TMUX_WCREATE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "c");
            }
            return false;
            break;

        case TMUX_WKILL:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "x");
            }
            return false;
            break;

        case TMUX_PFS:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "z");
            }
            return false;
            break;

        case TMUX_PLAST:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") ";");
            }
            return false;
            break;

        case TMUX_PSPLITV:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "%");
            }
            return false;
            break;

        case TMUX_PSPLITH:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "\"");
            }
            return false;
            break;

        case TMUX_PANE_UP:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") SS_TAP(X_UP));
            }
            return false;
            break;

        case TMUX_PANE_DOWN:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") SS_TAP(X_DOWN));
            }
            return false;
            break;

        case TMUX_PANE_RIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") SS_TAP(X_RIGHT));
            }
            return false;
            break;

        case TMUX_PANE_LEFT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") SS_TAP(X_LEFT));
            }
            return false;
            break;

        case DOEXIT:
            if (record->event.pressed) {
                SEND_STRING("exit" SS_TAP(X_ENTER));
            }
            return false;
            break;

        case VIM_CMD_MODE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) ":");
            }
            return false;
            break;

        case TMUX_PANE_SELECT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") "q");
                // https://www.reddit.com/r/olkb/comments/4izhrp/qmk_oneshot_question/
                // https://github.com/algernon/ergodox-layout/commit/6b81e4765d7cc04381558e51b4167d7d7fb344a5
                layer_on(NUMPAD);
                set_oneshot_layer(NUMPAD, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            } else {
            }
            return false;
            break;

        case TMUX_PANE_SELECT2:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b") SS_LCTRL("b") "q");
                // https://www.reddit.com/r/olkb/comments/4izhrp/qmk_oneshot_question/
                // https://github.com/algernon/ergodox-layout/commit/6b81e4765d7cc04381558e51b4167d7d7fb344a5
                layer_on(NUMPAD);
                set_oneshot_layer(NUMPAD, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            } else {
            }
            return false;
            break;

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
                SEND_STRING("\\" SS_TAP(X_ENTER));
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

        case WR_HTTP:
            if (record->event.pressed) {
                SEND_STRING("http://");
            }
            return false;
            break;

        case WR_HTTPS:
            if (record->event.pressed) {
                SEND_STRING("https://");
            }
            return false;
            break;

        case WR_PROTO_COLON_SLASHSLASH:
            if (record->event.pressed) {
                SEND_STRING("://");
            }
            return false;
            break;

        case WR_LOCALHOST:
            if (record->event.pressed) {
                SEND_STRING("localhost");
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

        case WR_WORD_OPENETHEREUM:
            if (record->event.pressed) {
                SEND_STRING("openethereum");
            }
            return false;
            break;

        case WR_WORD_MULTIGETH_DASHED:
            if (record->event.pressed) {
                SEND_STRING("multi-geth");
            }
            return false;
            break;

        case WR_WORD_COREGETH_DASHED:
            if (record->event.pressed) {
                SEND_STRING("core-geth");
            }
            return false;
            break;

        case WR_WORD_EIP:
            if (record->event.pressed) {
                SEND_STRING("EIP");
            }
            return false;
            break;

        case WR_WORD_ECIP:
            if (record->event.pressed) {
                SEND_STRING("ECIP");
            }
            return false;
            break;

        case WR_WORD_SYSTEM:
            if (record->event.pressed) {
                SEND_STRING("system");
            }
            return false;
            break;

        case WR_WORD_ETCSYSTEMDSYSTEM:
            if (record->event.pressed) {
                SEND_STRING("/etc/systemd/system/");
            }
            return false;
            break;

        case WR_WORD_JOURNALCTL:
            if (record->event.pressed) {
                SEND_STRING("journalctl");
            }
            return false;
            break;

        case WR_WORD_MASTER:
            if (record->event.pressed) {
                SEND_STRING("master");
            }
            return false;
            break;

        case WR_WORD_MAKE:
            if (record->event.pressed) {
                SEND_STRING("make ");
            }
            return false;
            break;

        case WR_WORD_GETH:
            if (record->event.pressed) {
                SEND_STRING("geth");
            }
            return false;
            break;

        case WR_WORD_LINT:
            if (record->event.pressed) {
                SEND_STRING("lint");
            }
            return false;
            break;

        case WR_GOSRC_ETHEREUM_GOETHEREUM:
            if (record->event.pressed) {
                SEND_STRING("~/go/src/github.com/ethereum/go-ethereum/");
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

        case WR_WORD_ROTBLAUER:
            if (record->event.pressed) {
                SEND_STRING("rotblauer");
            }
            return false;
            break;

        case WR_WORD_OPENRPC:
            if (record->event.pressed) {
                SEND_STRING("openrpc");
            }
            return false;
            break;

        case WR_WORD_OPEN_RPC:
            if (record->event.pressed) {
                SEND_STRING("open-rpc");
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
                SEND_STRING("o" SS_TAP(X_ESCAPE) "k");
            }
            return false;
            break;

        case VIM_INS_LINE_ABOVE:
            if (record->event.pressed) {
                SEND_STRING("ko" SS_TAP(X_ESCAPE) "j");
            }
            return false;
            break;

        case VIM_NOH:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) ":noh" SS_TAP(X_ENTER));
            }
            return false;
            break;

        case VIM_BUFFER_PREV:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) ":bprev" SS_TAP(X_ENTER));
            }
            return false;
            break;

        case VIM_BUFFER_NEXT:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) ":bnext" SS_TAP(X_ENTER));
            }
            return false;
            break;

        case VIM_EXECUTE_FILE:
            if (record->event.pressed) {
                // :!%:p
                SEND_STRING(SS_TAP(X_ESCAPE) ":!\"%:p\"" SS_TAP(X_ENTER));
            }
            return false;
            break;

        case WR_WORD_P2P:
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
                SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_SPACE) "wl");
            }
            return false;
            break;

        case SPACEMACS_NEOTREE_TOGGLE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) " ft");
            }
            return false;
            break;

        case SPACEMACS_WINDOW_RIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_SPACE) "wh");
            }
            return false;
            break;

        case SPACEMACS_WINDOW_UP:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_SPACE) "wk");
            }
            return false;
            break;

        case SPACEMACS_WINDOW_DOWN:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_SPACE) "wj");
            }
            return false;
            break;

        case WR_BASH_INTERVAR:
            if (record->event.pressed) {
                SEND_STRING("${}" SS_TAP(X_LEFT));
            }
            return false;
            break;

        case WR_BASH_INTERFN:
            if (record->event.pressed) {
                SEND_STRING("$()" SS_TAP(X_LEFT));
            }
            return false;
            break;
    }

    return true;
};

// https://www.reddit.com/r/MechanicalKeyboards/comments/8vg1jq/qmk_tap_dance_dynamic_macros_help/
void macroFlagHelpLess(qk_tap_dance_state_t *state, void *user_data) {
    keyrecord_t kr;
    if (state->count == 1) {
        kr.event.pressed = true;
        process_record_user(WR_FLAGHELP, &kr);
    } else if (state->count == 2) {
        kr.event.pressed = true;
        process_record_user(WR_FLAGHELPLESS, &kr);
    }
}

// https://www.reddit.com/r/MechanicalKeyboards/comments/8vg1jq/qmk_tap_dance_dynamic_macros_help/
void macroTabOrTmuxLeadQ(qk_tap_dance_state_t *state, void *user_data) {
    keyrecord_t kr;
    if (state->count == 1) {
        kr.event.pressed = true;
        SEND_STRING(SS_TAP(X_TAB));
    } else if (state->count == 2) {
        kr.event.pressed = true;
        process_record_user(TMUX_PANE_SELECT, &kr);
    } else if (state->count == 3) {
        SEND_STRING(SS_LCTRL("b") SS_LCTRL("b") "q");
        layer_on(NUMPAD);
        set_oneshot_layer(NUMPAD, ONESHOT_START);
        clear_oneshot_layer_state(ONESHOT_PRESSED);
    }
}

void macroTodoDone(qk_tap_dance_state_t *state, void *user_date) {
    if (state->count == 1) {
        SEND_STRING("- [ ] ");
    } else if (state->count == 2) {
        SEND_STRING("- [x] ");
    }
}

uint32_t layer_state_set_user(uint32_t state) {
    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case CAPSLAYER:
            ergodox_right_led_1_on();
            break;
        case NUMPAD:
            ergodox_right_led_2_on();
            break;
        case SYMBOLS:
            ergodox_right_led_3_on();
            break;
        case MOTIONLAYER:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case QWIMAMU:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case GOLANDLAYER:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case MACROLAYER:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case FLAYER:
            ergodox_right_led_1_on();
            wait_ms(100);
            ergodox_right_led_1_off();
            wait_ms(100);
            ergodox_right_led_1_on();
            wait_ms(100);
            ergodox_right_led_1_off();
        case DEADQWERTY:
            ergodox_right_led_1_on();
            break;
        default:
            break;
    }
    return state;
};

/* --- */
// https://beta.docs.qmk.fm/using-qmk/software-features/feature_tap_dance

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        /* if (state->interrupted || !state->pressed)  return SINGLE_TAP; */
        if (!state->pressed) return SINGLE_TAP;
        // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
         */
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8;  // magic number. At some point this method will expand to work for more presses
}

// instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {.is_press_action = true, .state = 0};

void alt_uni_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            // Something?
        case SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        case DOUBLE_TAP:
            layer_on(UNICODEL);
            set_oneshot_layer(UNICODEL, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
    }
};

void alt_uni_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
            /* case DOUBLE_TAP: */
            /* clear_oneshot_layer_state(ONESHOT_PRESSED); */
    }
    xtap_state.state = 0;
};

// shift_cap is a custom shift (via the capslayer, since my actual capslock is eternally
// fucked because of my x settings which have fucked it for all keyboards. so i use a custom layer
// to be capslock).
// - on one tap, it's effectively one-shot modifier for shift.
// - on one hold, it's shift
// - on two taps, it's capslock
void shift_cap_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            /* layer_on(CAPSLAYER); */
            if (layer_state_is(CAPSLAYER)) {
                layer_off(CAPSLAYER);
            } else {
                set_oneshot_layer(CAPSLAYER, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            }
            break;
        case SINGLE_HOLD:
            register_code(KC_LSHIFT);
            break;
        case DOUBLE_TAP:
            if (layer_state_is(CAPSLAYER)) {
                layer_off(CAPSLAYER);
            } else {
                layer_on(CAPSLAYER);
            }
            break;
        case DOUBLE_HOLD:
            register_code(KC_LSHIFT);
            break;
    }
};

void shift_cap_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LSHIFT);
            break;
        case DOUBLE_TAP:
            break;
        case DOUBLE_HOLD:
            unregister_code(KC_LSHIFT);
            break;
    }
    xtap_state.state = 0;
};

void oneormore_symbols_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            /* layer_on(SYMBOLS); */
            set_oneshot_layer(SYMBOLS, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case SINGLE_HOLD:
            layer_on(SYMBOLS);
            break;
        case DOUBLE_TAP:
            layer_invert(SYMBOLS);
            break;
        case DOUBLE_HOLD:
            register_code(KC_LCTL);
            break;
    }
};

void oneormore_symbols_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            layer_off(SYMBOLS);
            break;
        case DOUBLE_TAP:
            break;
        case DOUBLE_HOLD:
            unregister_code(KC_LCTL);
            break;
    }
    xtap_state.state = 0;
};

void x_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_X);
            break;
        case SINGLE_HOLD:
            register_code(KC_LCTRL);
            break;
        case DOUBLE_TAP:
            register_code(KC_ESC);
            break;
        case DOUBLE_HOLD:
            register_code(KC_LALT);
            break;
        case DOUBLE_SINGLE_TAP:
            register_code(KC_X);
            unregister_code(KC_X);
            register_code(KC_X);
            // Last case is for fast typing. Assuming your key is `f`:
            // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
            // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
};

void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_X);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LCTRL);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_ESC);
            break;
        case DOUBLE_HOLD:
            unregister_code(KC_LALT);
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_X);
    }
    xtap_state.state = 0;
};

void fancyfancy_awesome_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LSHIFT);
            tap_code(KC_QUOTE);
            unregister_code(KC_LSHIFT);
            break;
        case DOUBLE_TAP:
            register_code(KC_LSHIFT);
            tap_code(KC_SLASH);
            unregister_code(KC_LSHIFT);
            break;
    }
};

void fancyfancy_awesome_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_TAP:
            break;
    }
    xtap_state.state = 0;
};

void awesome_fb_tag_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LGUI);
            tap_code(KC_RIGHT);
            unregister_code(KC_LGUI);
            break;
        case SINGLE_HOLD:
            register_code(KC_LSHIFT);
            layer_on(MOTIONLAYER);
            break;
        case DOUBLE_TAP:
            register_code(KC_LGUI);
            tap_code(KC_LEFT);
            unregister_code(KC_LGUI);
            break;
    }
};

void awesome_fb_tag_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LSHIFT);
            layer_off(MOTIONLAYER);
            break;
        case DOUBLE_TAP:
            break;
    }
    xtap_state.state = 0;
};

void awesome_next_tag_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    // CTLGUI(KC_K) : next/previous screen
    // LGUI(KC_ENTER) : next/previous app
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LGUI);
            tap_code(KC_TAB);
            unregister_code(KC_LGUI);
            break;
        case SINGLE_HOLD:
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            break;
        case DOUBLE_TAP:
            register_code(KC_LGUI);
            register_code(KC_LCTL);
            tap_code(KC_K);
            unregister_code(KC_LGUI);
            unregister_code(KC_LCTL);
            break;
    }
};

void awesome_next_tag_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            break;
        case DOUBLE_TAP:
            break;
    }
    xtap_state.state = 0;
};

void bash_intervar_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            process_record_user(WR_BASH_INTERVAR, NULL);
            break;
        case DOUBLE_TAP:
            process_record_user(WR_BASH_INTERFN, NULL);
            break;
    }
};

void bash_intervar_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
    }
    xtap_state.state = 0;
};

void tmux2_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            process_record_user(TMUX_LEADER2, NULL);
            break;
    }
};

void tmux2_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
    }
    xtap_state.state = 0;
};

// macro_LEADER_or_TmuxLeadQ
void macro_LEADER_or_TmuxLeadQ_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    // CTLGUI(KC_K) : next/previous screen
    // LGUI(KC_ENTER) : next/previous app
    switch (xtap_state.state) {
        case SINGLE_TAP:
            process_record_user(TMUX_PANE_SELECT, NULL);
            break;
        case DOUBLE_TAP:
            process_record_user(TMUX_PANE_SELECT2, NULL);
            break;
        case SINGLE_HOLD:
            register_code(KC_LGUI);
            tap_code(KC_Z);
            unregister_code(KC_LGUI);
            break;
        case DOUBLE_HOLD:
            register_code(KC_LGUI);
            tap_code(KC_Y);
            unregister_code(KC_LGUI);
            break;

    }
}

void macro_LEADER_or_TmuxLeadQ_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_TAP:
            break;
        case SINGLE_HOLD:
            break;
        case DOUBLE_HOLD:
            break;
    }
    xtap_state.state = 0;
};

void alt_question_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    // CTLGUI(KC_K) : next/previous screen
    // LGUI(KC_ENTER) : next/previous app
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LSHIFT);
            register_code(KC_SLASH);
            break;
        case SINGLE_HOLD:
            register_code(KC_LALT);
            break;
    }
};

void alt_question_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_LSHIFT);
            unregister_code(KC_SLASH);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
    }
    xtap_state.state = 0;
};

void copy_paste_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    // CTLGUI(KC_K) : next/previous screen
    // LGUI(KC_ENTER) : next/previous app
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_C);
            break;
        case DOUBLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_V);
            break;
        case TRIPLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_X);
            break;
    }
};

void copy_paste_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_C);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_V);
            break;
        case TRIPLE_TAP:
            unregister_code(KC_LCTL);
            unregister_code(KC_X);
            break;
    }
    xtap_state.state = 0;
};

void tobase_and_clean_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TRIPLE_TAP:
            layer_move(BASE);

            clear_keyboard();
            clear_mods();

            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            wait_ms(300);
            ergodox_right_led_1_off();
            ergodox_right_led_2_off();
            ergodox_right_led_3_off();

            break;
        case TRIPLE_HOLD:
            reset_keyboard();
    }
};

void tobase_and_clean_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TRIPLE_TAP:
            break;
        case TRIPLE_HOLD:
            break;
    }
    xtap_state.state = 0;
};

void awesomewm_selecttag_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            register_code(KC_LGUI);
            layer_on(NUMPAD);
            break;
    }
};

void awesomewm_selecttag_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LGUI);
            if (layer_state_is(NUMPAD)) {
                layer_off(NUMPAD);
            }
            break;
    }
    xtap_state.state = 0;
};

void td_lgui_doublequote_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LSHIFT);
            tap_code(KC_QUOTE);
            unregister_code(KC_LSHIFT);
            break;
        case SINGLE_HOLD:
            register_code(KC_LGUI);
            break;
    }
};

void td_lgui_doublequote_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LGUI);
            break;

    }
    xtap_state.state = 0;
};

void td_mouse_backforward_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_MS_BTN4);
            break;
        case DOUBLE_TAP:
            tap_code(KC_MS_BTN5);
            break;
    }
};

void td_mouse_backforward_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_TAP:
            break;
    }
    xtap_state.state = 0;
};

void td_fancy_codefence_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            process_record_user(WR_CODEFENCE, NULL);
            break;
        case DOUBLE_TAP:
            tap_code(KC_ENTER);
            process_record_user(WR_CODEFENCE, NULL);
            tap_code(KC_ENTER);
            tap_code(KC_ENTER);
            process_record_user(WR_CODEFENCE, NULL);
            tap_code(KC_UP);
            break;
    }
};

void td_fancy_codefence_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_TAP:
            break;
    }
    xtap_state.state = 0;
};

void td_left_lower_thumb_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            layer_invert(CAPSLAYER);
            break;
    }
};

void td_left_lower_thumb_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
    }
    xtap_state.state = 0;
};

void td_right_lower_thumb_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            process_record_user(TMUX_LEADER,  NULL);
            break;
    }
};

void td_right_lower_thumb_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
    }
    xtap_state.state = 0;
};


void td_top_right_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_LGUI);
            tap_code(KC_ENTER);
            unregister_code(KC_LGUI);
            break;
        case DOUBLE_TAP:
            break;
        case SINGLE_HOLD:
            register_code(KC_LGUI);
            tap_code(KC_N);
            unregister_code(KC_LGUI);
            break;
        case DOUBLE_HOLD:
            register_code(KC_LGUI);
            register_code(KC_LCTL);
            tap_code(KC_N);
            unregister_code(KC_LGUI);
            unregister_code(KC_LCTL);
            break;
    }
};

void td_top_right_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_TAP:
            break;
        case SINGLE_HOLD:
            break;
        case DOUBLE_HOLD:
            break;
    }
    xtap_state.state = 0;
};


qk_tap_dance_action_t tap_dance_actions[] = {
    // 
    [TD_CURLYBRACKET]           = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
                                             [TD_PAREN]                  = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_PAREN, KC_RIGHT_PAREN),
                                             [TD_BRACKET]                = ACTION_TAP_DANCE_DOUBLE(KC_LBRACKET, KC_RBRACKET),
                                             [TD_QUOTE_COUNTERINTUITIVE] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_QUOTE), KC_QUOTE),
                                             [TD_HYPHEN_EQUALS]          = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, KC_EQUAL),
                                             [TD_LABK_COMMA]             = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_COMMA),
                                             [TD_RABK_DOT]               = ACTION_TAP_DANCE_DOUBLE(KC_RABK, KC_DOT),

                                             /* [TD_HELPFLAG] = ACTION_TAP_DANCE_DOUBLE(WR_FLAGHELP, WR_FLAGHELPLESS), */
                                             [TD_HELPFLAG]  = ACTION_TAP_DANCE_FN(macroFlagHelpLess),
                                             [TD_TAB_TMUXQ] = ACTION_TAP_DANCE_FN(macroTabOrTmuxLeadQ),
                                             //                                             [TD_LEADER_TMUXQ]          = ACTION_TAP_DANCE_FN(macro_LEADER_or_TmuxLeadQ),
                                             [TD_LEADER_TMUXQ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, macro_LEADER_or_TmuxLeadQ_finished, macro_LEADER_or_TmuxLeadQ_reset),  // ACTION_TAP_DANCE_FN(macro_LEADER_or_TmuxLeadQ),
                                                                                                                                                                           //                                             [TD_QUESTION_TOPROWNUM] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_QUESTION, TOPROWNUM),
                                             [TD_DQUOTE_MOTION] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_DOUBLE_QUOTE, MOTIONLAYER),
                                             [TD_TODO_DONE]     = ACTION_TAP_DANCE_FN(macroTodoDone),

                                             [X_CTL]                          = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
                                             [TD_ALT_UNI]                        = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_uni_finished, alt_uni_reset),
                                             [TD_SHIFT_CAP]                      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_cap_finished, shift_cap_reset),
                                             [ONEORMO_SYMBOLS]                = ACTION_TAP_DANCE_FN_ADVANCED(NULL, oneormore_symbols_finished, oneormore_symbols_reset),
                                             [TD_FANCYAWESOMEQUOTE]           = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fancyfancy_awesome_quote_finished, fancyfancy_awesome_reset),
                                             [AWESOME_TAG_FORWARD_BACK]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, awesome_fb_tag_finished, awesome_fb_tag_reset),
                                             [AWESOME_TAG_NEXT_SCREEN_OR_APP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, awesome_next_tag_finished, awesome_next_tag_reset),
                                             [TD_BASH_INTERVAR]               = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bash_intervar_finished, bash_intervar_reset),
                                             [TD_TMUX2]                       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tmux2_finished, tmux2_reset),
                                             [TD_ALT_QUESTION]                = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_question_finished, alt_question_reset),
                                             [TD_COPY_PASTE]                  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copy_paste_finished, copy_paste_reset),
                                             [TD_TOBASE_CLEAN]                = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tobase_and_clean_finished, tobase_and_clean_reset),
                                             [TD_AWESOME_SELECT_TAG]          = ACTION_TAP_DANCE_FN_ADVANCED(NULL, awesomewm_selecttag_finished, awesomewm_selecttag_reset),
                                             [TD_LGUI_DOUBLEQUOTE]            = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lgui_doublequote_finished, td_lgui_doublequote_reset),
                                             [TD_MOUSE_BACKFORWARD]           = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_mouse_backforward_finished, td_mouse_backforward_reset),
                                             [TD_FANCY_CODEFENCE]             = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_fancy_codefence_finished, td_fancy_codefence_reset),
                                             [TD_LEFT_BLUE_THUMB]             = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_left_lower_thumb_finished, td_left_lower_thumb_reset),
                                             [TD_RIGHT_BLUE_THUMB]             = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_right_lower_thumb_finished, td_right_lower_thumb_reset),
                                             [TD_TOP_RIGHT_0]             = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_top_right_0_finished, td_top_right_0_reset),
};
