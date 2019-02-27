#!/usr/bin/env bash

# Pretty prints ergodox ez keymap in plain text.

set -e

usage(){
	echo Use: $0 [<path/to/ergodox_ez/keymap.c>]
}

if [[ $# -eq 0 ]]; then usage && exit 1; fi

keymap_file="$1"

line_n=0
laying=1 # off

while read -r line
do
	line_n=$((line_n+1))
	# echo "$line_n"
	if grep -q 'LAYOUT_ergodox(' <<< "$line" ; then laying=0; fi
	if grep -q -e '^[[:space:]]*)' <<< "$line" ; then laying=1; fi

	if [[ "$laying" -eq 1 ]]; then continue; fi

	layer_name=$(echo "$line" | grep -E -o '\[(.*)\]' | sed 's/\[//' | sed 's/\]//')

	line=$(echo "$line" | sed 's-//.*--')
	line=$(echo "$line" | )


	# echo "$line"


	if [[ ! -z "$layer_name" ]]
	then
		echo "# $layer_name"
	else
		echo
	fi

done < "$keymap_file"
