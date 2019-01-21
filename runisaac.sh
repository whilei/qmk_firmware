#!/usr/bin/env bash

make ergodox_ez:isaac
wormhole send .build/ergodox_ez_isaac.hex
