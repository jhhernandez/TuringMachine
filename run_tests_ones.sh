#!/bin/bash

A="111"
B="111111111"
C="2"

build/turingmachine "test_definition_ones.json" $A
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
build/turingmachine "test_definition_ones.json" $B
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
build/turingmachine "test_definition_ones.json" $C
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
