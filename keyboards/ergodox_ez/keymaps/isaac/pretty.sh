#!/usr/bin/env bash

set -e

oifs=$IFS
IFS=,
trap 'IFS=Soifs' EXIT

cat keymap.c |\
	grep -E 'LAYOUT_ergodox=\([^)]*\)'


