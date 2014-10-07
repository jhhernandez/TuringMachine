#!/bin/bash

A="a"
B="aaabbaab"
C="aabbbbabbbabbab"
D="ab"
E="aaaabbbbbbbbbbbb"

build/turingmachine "test_definition" $A
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
build/turingmachine "test_definition" $B
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
build/turingmachine "test_definition" $C
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

build/turingmachine "test_definition2" $A
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
build/turingmachine "test_definition2" $D
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
build/turingmachine "test_definition2" $E
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi