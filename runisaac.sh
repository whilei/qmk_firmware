#!/usr/bin/env bash

set -e

make ergodox_ez:isaac
# wormhole send .build/ergodox_ez_isaac.hex

echo "What next?"
select yn in "Teensy" "Quit"; do
	case $yn in
		Teensy ) sudo ./bin/teensy ;;
		Quit ) xset r rate 170 50; exit;;
	esac
done


