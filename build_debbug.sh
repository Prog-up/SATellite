#!/bin/bash

mkdir build
cd build
gcc -g -c -Wall -Ofast ../src/*.c
gcc -g -Wall -Ofast *.o -o SATellite

rm -f *.o