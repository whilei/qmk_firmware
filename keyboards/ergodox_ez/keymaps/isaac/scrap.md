// Contains scrap stuff that I don't use but might come in handy later.

### Includes


```
/* #include "keymap_german.h" */
/* #include "keymap_nordic.h" */
```

### Layers

```
    /* [DELAYER] = LAYOUT_ergodox( */
    /*                           // Left */
    /*                           ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
    /*                           ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
    /*                           ___ , DE_AE , DE_SS , DE_EURO , ___ , ___ , */
    /*                           ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
    /*                           ___ , ___ , ___ , ___ , ___ , */
    /*                           ___ , ___ , */
    /*                           ___ , */
    /*                           ___ , ___ , ___ , */

    /*                           // right */

    /*                           ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
    /*                           ___ , ___ , DE_UE , ___ , ___ , ___ , ___ , */
    /*                           ___ , ___ , ___ , DE_OE , ___ , ___ , */
    /*                           ___ , ___ , ___ , ___ , ___ , ___ , ___ , */
    /*                           ___ , ___ , ___ , ___ , ___ , */
    /*                           ___ , ___ , */
    /*                           ___ , */
    /*                           ___ , ___ , ___ */

    /*                       ), */

   //    [TOPROWALT] = LAYOUT_ergodox(
    //        // Left
    //        ___, ___, ___, ___, ___, ___, ___,  // /
    //        ___, ___, ___, ___, ___, ___, ___,  // /
    //        ___, ___, ___, ___, ___, ___,       // /
    //        ___, ___, ___, ___, ___, ___, ___,  // /
    //        ___, ___, ___, ___, ___,            // /
    //        ___, ___,                           // /
    //        ___,                                // /
    //        ___, ___, ___,                      // /
    //
    //    // right
    //
    //        ___, ___, ___, ___, ___, ___, ___,  // /
    //        ___, ___, ___, ___, ___, ___, ___,  // /
    //        ___, ___, ___, ___, ___, ___,       // /
    //        ___, ___, ___, ___, ___, ___, ___,  // /
    //        ___, ___, ___, ___, ___,            // /
    //        ___, ___,                           // /
    //        ___,                                // /
    //        ___, ___, ___                       // /
    //
    //    ),
    //
    //    [TOPROWNUM] = LAYOUT_ergodox(
    //        // Left
    //        /* ___ , KC_0 , KC_1 , KC_2 , KC_3 , KC_4 , ___ , */
    //        ___, KC_1, KC_2, KC_3, KC_4, KC_5, ___,  // /
    //        ___, ___, ___, ___, ___, ___, ___,       // /
    //        ___, ___, ___, ___, ___, ___,            // /
    //        ___, ___, ___, ___, ___, ___, ___,       // /
    //        ___, ___, ___, ___, ___,                 // /
    //        ___, ___,                                // /
    //        ___,                                     // /
    //        ___, ___, ___,                           // /
    //
    //    // right
    //    /* ___ , KC_5 , KC_6 , KC_7 , KC_8 , KC_9 , ___ , */
    //        ___, KC_6, KC_7, KC_8, KC_9, KC_0, ___, ___, ___, ___, ___, ___, ___, ___,  // /
    //        ___, ___, ___, ___, ___, ___,                                               // /
    //        ___, ___, ___, ___, ___, ___, ___,                                          // /
    //        ___, ___, ___, ___, ___,                                                    // /
    //        ___, ___,                                                                   // /
    //        ___,                                                                        // /
    //        ___, ___, ___                                                               // /
    //    )

    /*
     *     // DISUSED
    [MOUSELAYER] = LAYOUT_ergodox(

        // Left
        ___, ___, ___, ___, ___, ___, ___,                   // /
        ___, ___, ___, KC_MS_UP, ___, ___, ___,              // /
        ___, ___, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, ___,  // /
        ___, ___, ___, ___, ___, ___, ___,                   // /
        ___, ___, ___, ___, ___,                             // /
        ___, ___,                                            // /
        KC_MS_BTN4,                                          // /
        KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN5,                  // /

        // right
        ___, ___, ___, ___, ___, ___, ___,  // /
        ___, ___, ___, ___, ___, ___, ___,  // /
        ___, ___, ___, ___, ___, ___,       // /
        ___, ___, ___, ___, ___, ___, ___,  // /
        ___, ___, ___, ___, ___,            // /
        ___, ___,                           // /
        ___,                                // /
        ___, ___, ___                       // /

        ),
     */

    /*
     *
    [XPLANE] = LAYOUT_ergodox(
        // Left
        KC_BSLASH, ___, ___, KC_MINUS, KC_R, KC_EQUAL, KC_RETURN,  // toggle instrumentation descriptions on hover ; view: zoom out, tilt up, zoom in; contact ATC
        KC_SCOLON, LSFT(KC_9), ___, KC_Q, KC_F, KC_E, KC_1,        // toggle clickable cockpit areas ; view: pan left, tilt down, pan right; flaps up a notch
        ___, ___, ___, KC_COMMA, KC_UP, KC_DOT,                    // view: backward, up, forward
        KC_SPACE, ___, ___, KC_LEFT, KC_DOWN, KC_RIGHT, KC_2,      // general action cmd ; view: move left, down, right ; flaps down a notch
        ___, ___, ___, KC_G, KC_B,                                 // landing gear, brakes
        KC_8, KC_0,                                                // roll trim left, right
        KC_LBRACKET,                                               // pitch trim down
        KC_F1, KC_F2, KC_RBRACKET,                                 // throttle down, up ; pitch trim up

        // right
        ___, ___, ___, ___, ___, ___, ___,  // /
        ___, ___, ___, ___, ___, ___, ___,  // /
        ___, ___, ___, ___, ___, ___,       // /
        ___, ___, ___, ___, ___, ___, ___,  // /
        ___, ___, ___, ___, ___,            // /
        ___, ___,                           // /
        ___,                                // /
        ___, ___, ___                       // /
        ),
     */
```

---

### Unicodes

```
    /* [UNIC_TEA] = 0x1F375 // :tea: */
    /* [UNIC_BANG]  = 0x203D,  // ‽ */
    /* [UNIC_IRONY] = 0x2E2E,  // ⸮ */
    /* [UNIC_OBELISM] = 0x205B // ⁛ */
    /* [UNIC_THUMPSDN] = 0x1F44E // :-1: */
```

### Macros

```

            /* case LOCK_SHIFT: */
            /*   if (record->event.pressed) { */
            /*     tap_code(X_LOCK); */
            /*     tap_code(X_LSHIFT); */
            /*   } */
            /*   return false; */
            /*   break; */

            /* #ifdef UNICODE_ENABLE */
            /*   case EMOJI_UHU: */
            /*     if (record->event.pressed) { */
            /*       send_unicode_hex_string("2299 FE4F 2299"); */
            /*     } */
            /*     return false; */
            /*     break; */

            /*   case EMOJI_FACE2: */
            /*     if (record->event.pressed) { */
            /*       send_unicode_hex_string("0028 2022 005F 2022 0029"); */
            /*     } */
            /*     return false; */
            /*     break; */

            /*   case EMOJI_FACE1: */
            /*     if (record->event.pressed) { */
            /*       send_unicode_hex_string("0028 002D 005F 002D 0029"); */
            /*     } */
            /*     return false; */
            /*     break; */

            /*   case EMOJI_EGGY2: */
            /*     if (record->event.pressed) { */
            /*       send_unicode_hex_string("30CE 0028 0020 309C 002D 309C 30CE 0029"); */
            /*     } */
            /*     return false; */
            /*     break; */

            /*   case EMOJI_SMILE2: */
            /*     if (record->event.pressed) { */
            /*       send_unicode_hex_string("0028 0298 203F 0298 0029"); */
            /*     } */
            /*     return false; */
            /*     break; */

            /*   case EMOJI_SHRUG: // // ¯\_(ツ)_/¯ */
            /*     if (record->event.pressed) { */
            /*       send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF"); */
            /*     } */
            /*     return false; */
            /*     break; */
            /* #endif */

            /* case EMOJI_YAY: */
            /*   if (record->event.pressed) { */
            /*     SEND_STRING ("\\o/"); */
            /*   } */
            /*   return false; */
            /*   break; */
```

### Tap dance logics
```
            //        case SINGLE_HOLD:
            //            if (!layer_state_is(NUMPAD)) {
            //                layer_on(NUMPAD);
            //            }
            //            register_code(KC_LGUI);
            //            break;
            //        case DOUBLE_HOLD:
            //            if (!layer_state_is(NUMPAD)) {
            //                layer_on(NUMPAD);
            //            }
            //            register_code(KC_LGUI);
            //            register_code(KC_LSHIFT);
            //            break;
            /* case DOUBLE_TAP: register_code(KC_ESC); break; */
            /* case DOUBLE_HOLD: register_code(KC_LALT); break; */
            /* case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X); */
            
                        //        case SINGLE_HOLD:
            //            if (layer_state_is(NUMPAD)) {
            //                layer_off(NUMPAD);
            //            }
            //            unregister_code(KC_LGUI);
            //            break;
            //        case DOUBLE_HOLD:
            //            if (layer_state_is(NUMPAD)) {
            //                layer_off(NUMPAD);
            //            }
            //            unregister_code(KC_LGUI);
            //            unregister_code(KC_LSHIFT);
            //            break;
            /* case DOUBLE_TAP: unregister_code(KC_ESC); break; */
            /* case DOUBLE_HOLD: unregister_code(KC_LALT); */
            /* case DOUBLE_SINGLE_TAP: unregister_code(KC_X); */
```


```

```