#!/bin/bash

TM=build/turingmachine
TEST="test_mt_definition.json"
A="aaaaaa"
B="aaabbaab"
C="aabbbbabbbabbab"

$TM $TEST $A","
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

$TM $TEST $B","
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi

$TM $TEST $C","
if [ $? = 0 ]; then
	echo valid string
else
	echo invalid string
fi
