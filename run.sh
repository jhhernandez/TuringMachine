#!/bin/bash

A="a"
B="aaabbaab"
C="aabbbbabbbabbab"

build/turingmachine "maquina.json" $A
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
build/turingmachine "maquina.json" $B
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
build/turingmachine "maquina.json" $C
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
