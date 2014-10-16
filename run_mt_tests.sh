#!/bin/bash

A="aaaaaa"
B="aaabbaab"
C="aabbbbabbbabbab"

build/turingmachine "test_mt_definition.json" $A","
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

build/turingmachine "test_mt_definition.json" $B","
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

build/turingmachine "test_mt_definition.json" $C","
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
