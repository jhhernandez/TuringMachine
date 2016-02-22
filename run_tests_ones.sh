#!/bin/bash

TM=build/turingmachine
TEST="test_definition_ones.json"
A="111"
B="111111111"
C="2"

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
