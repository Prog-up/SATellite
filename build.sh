#!/bin/bash

mkdir build
cd build
gcc -c -Wall -Ofast ../src/*.c
gcc -Wall -Ofast *.o -o SATellite

rm -f *.o