//------------------------------
// Include all files and and
// parse command line arguments.
//------------------------------

#include <stdio.h>
#include "../include/parse_dimacs.h"

void test0(char* fn) {
    /*Testing parse_dimacs*/
    
    CNF* f = parse_cnf(fn);
    print_CNF(f);
    free_CNF(f);
}

int main(int argc, char** argv) {
    
    test0(argv[1]);
    return 0;
}