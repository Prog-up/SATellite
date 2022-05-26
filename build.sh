#!/bin/bash

mkdir build
cd build
gcc -c -Wall -Ofast ../src/*.c -lm
gcc -Wall -Ofast *.o -o SATellite -lm

rm -f *.o