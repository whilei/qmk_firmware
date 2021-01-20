#!/usr/bin/env bash

set -e

build() {
  make ergodox_ez:isaac
}

main() {
  echo "What next?"

  # Give option for rebuilding if this is not being run the first time.
  local myopts=("Build" "Teensy" "Quit")
  test "${1}" == 0 && myopts=("${myopts[@]:1}")

  select yn in "${myopts[@]}"; do
    case $yn in
      Build ) build ;;
      Teensy ) sudo make ergodox_ez:isaac:teensy; xset r rate 192 50; main 1;;
      Quit ) xset r rate 192 50; exit;;
    esac
  done
}

build
main 0



