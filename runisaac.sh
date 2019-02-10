#!/usr/bin/env bash

set -e

make ergodox_ez:isaac
# wormhole send .build/ergodox_ez_isaac.hex
./bin/teensy
