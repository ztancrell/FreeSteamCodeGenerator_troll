#!/bin/bash

SRC="src/FreeSteamGenerator.cpp"
OUT="build/FreeSteamCodeGenerator"
STD="c++11"
CMD="g++ -std=${STD} -o ${OUT} ${SRC} -pthread"

echo "Building with: $CMD"
echo "C++ standard version: $STD"
$CMD

echo ""
