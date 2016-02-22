#!/bin/bash

TM=build/turingmachine
TEST="test_definition2.json"
A="a"
B="bba"
C="ab"
D="aaaabbbbbbbbbbbb"

$TM $TEST $A
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

$TM $TEST $B
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

$TM $TEST $C
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

$TM $TEST $D
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi