//------------------------------
// Tests
//------------------------------

//---Include
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "../include/types.h"
#include "../include/parse_dimacs.h"
#include "../include/dpll.h"
#include "../include/quine.h"

//---Check model
bool check_model(CNF* formula, int* val) {
    /*Checks if the model satisfies the formula.*/

    struct CNF_clause* f = formula->f;
    Clause c;

    while (f != NULL) {
        c = f->c;
        bool sat = true;

        while (c != NULL) {
            if (c->l < 0)
                sat = sat || (!val[-(c->l) - 1]);
            else
                sat = sat || (val[c->l - 1]);
            
            c = c->next;
        }

        if (!sat)
            return false;
        
        f = f->next;
    }

    return true;
}


//---Test a formula on a file
bool test_formula(char* fn, bool expected, char* algo, char* heur) {
    /*
    Test if the formula is as expected.
    
    - fn       : the file name ;
    - expected : the expectation of the satisfiability of the formula ;
    - algo     : the algorithm name (quine or dpll) ;
    - heur     : the heuristic name.
    */

    CNF* formula = parse_cnf(fn);

    //---Create val array
    int n = formula->varc;
    int* val = (int*) malloc(n * sizeof(int));
    for (int k = 0 ; k < n ; k++) {
        val[k] = -1;
    }

    printf("Testing '%s' (algo : %s, heur : %s) ...\n", fn, algo, heur);

    //---Run solver
    bool sat;
    clock_t t = clock();

    if (strcmp(algo, "quine") == 0)
        sat = quine(formula, &val, n);
    else
        sat = dpll(formula, heur, &val, n);

    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC;
    
    //---Check result
    if (sat != expected) {
        printf("SATellite: Test error: file '%s': wrong bool value (algo : %s, heur : %s)\n", fn, algo, heur);
        free(val);
        free_CNF(formula);
        return false;
    }

    if (!sat) {
        free(val);
        free_CNF(formula);
        printf("File '%s': Good, took %.3lf sec\n", fn, time_taken);
        return true;
    }

    if (!check_model(formula, val)) {
        printf("SATellite: Test error: file '%s': wrong valuation (algo : %s, heur : %s)\n", fn, algo, heur);
        free(val);
        free_CNF(formula);
        return false;
    }

    //free(val);
    free_CNF(formula);
    printf("File '%s': Good, took %.3lf sec\n", fn, time_taken);
    return true;
}


//---Test a directory
bool test_dir(char* dirname, bool expected, char* algo, char* heur) {
    /*
    Test all CNF files in the dir `dirname`.
    
    - dirname  : the directory's name ;
    - expected : the expected satisfiability for the formulae in `dirname` ;
    - algo     : the algorithm name (quine or dpll) ;
    - heur     : the heuristic name.
    */

    DIR *d;
    struct dirent *dir;
    bool correct;

    if (strcmp("quine", algo) == 0)
        printf("\n------\nTesting directory '%s' with Quine algorithm\n", dirname);
    else
        printf("\n------\nTesting directory '%s' with DPLL algorithm using %s heuristic\n", dirname, heur);

    d = opendir(dirname);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strstr(dir->d_name, ".cnf")) { // check if files names contains ".cnf"
                char cnf_name[255];
                strcpy(cnf_name, dirname);
                strcat(cnf_name, dir->d_name);

                correct = test_formula(cnf_name, expected, algo, heur);

                if (!correct)
                    return false;
            }
        }
        closedir(d);
    }

    return true;
}

//---Test all
bool test_all() {
    /*Test SATellite.*/

    char* heurs[5] = {"first", "random", "jw", "jw2", "freq"};
    char* sat_dirs[4] = {"test/SAT/uf20/", "test/SAT/uf50/", "test/SAT/uf75/", "test/SAT/uf100/"};
    char* unsat_dirs[3] = {"test/UNSAT/uuf50/", "test/UNSAT/uuf75/", "test/UNSAT/uuf100/"};

    //------Quine
    //---SAT
    if (!test_dir("test/SAT/uf20/", true, "quine", "first"))
        return false;

    //---UNSAT
    if (!test_dir("test/UNSAT/", false, "quine", "first"))
        return false;
    
    //------DPLL
    for (int i = 0 ; i < 5 ; i++) { //heurs
        for (int j = 0 ; j < 4 ; j++) { //dirs
            if (!test_dir(sat_dirs[j], true, "dpll", heurs[i]))
                return false;

            if (j != 4 && !test_dir(unsat_dirs[j], false, "dpll", heurs[i]))
                return false;
        }
    }

    return true;
}
