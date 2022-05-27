#!/bin/bash

mkdir build
cd build
gcc -g -c -Wall -Ofast ../src/*.c -lm
gcc -g -Wall -Ofast *.o -o SATellite -lm

rm -f *.o
