#!/bin/bash

A="a"
B="bba"
C="ab"
D="aaaabbbbbbbbbbbb"

build/turingmachine "test_definition2.json" $A
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

build/turingmachine "test_definition2.json" $B
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

build/turingmachine "test_definition2.json" $C
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

build/turingmachine "test_definition2.json" $D
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi