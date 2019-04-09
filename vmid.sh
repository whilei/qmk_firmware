#!/usr/bin/env bash

homesteadops=$(evmasm -t | sed '/REVERT/d;/DELEGATE/d;/STATIC/d;' | cut -d':' -f1 | while read op; do echo $((op)); done)
byzantiumops=$(evmasm -t | cut -d':' -f1 | while read op; do echo $((op)); done)


# @1 - opcode table as above
word_bin(){
for i in $(seq 0 255); do
	grep -q "^$i$" <<< "$1" && printf 1 || printf 0
done
}

homestead_word_bin="$(word_bin "$homesteadops")"
byzantium_word_bin="$(word_bin "$byzantiumops")"

echo "homestead vm id:"
echo "obase=16;ibase=2;$homestead_word_bin" | bc

echo "byzantium vm id:"
echo "obase=16;ibase=2;$byzantium_word_bin" | bc
