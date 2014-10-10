#!/bin/bash

A="a"
B="bba"
C="ab"
D="aaaabbbbbbbbbbbb"

build/turingmachine "test_definition2" $A
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

build/turingmachine "test_definition2" $B
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

build/turingmachine "test_definition2" $C
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