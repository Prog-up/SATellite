mkdir build
cd build
gcc.exe -c -Wall -Ofast ../src/*.c
gcc.exe -Wall -Ofast *.o -o SATellite.exe
del *.o rem Not sure of this