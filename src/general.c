//------------------------------
// General functions used in
// several files.
//------------------------------

//------Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../include/quine.h"
#include "../include/dpll.h"
#include "../include/general.h"


//------Eval
void eval(CNF* formula, int x, bool v) {
    /*
    Evaluate the formula at x with value v. It modifies the input formula.
    
    Input :
        - formula : the CNF* formula ;
        - x       : the variable ;
        - v       : the value that should take the variable.
    
    Output :
        the formula, where all clause where there is `x` are removed, and where -`x` is removed from all clauses.
    */

    if (v == false) {
        return eval(formula, -x, true);
    }

    struct CNF_clause* f = formula->f;
    struct CNF_clause* f0 = f;

    int cc = formula->cc;
    int varc = formula->varc;

    while (f != NULL) {
        Clause c = f->c;
        Clause c0 = c;

        bool go_next = true;
        while (c != NULL) {
            if (c->l == x) {
                if (f == f0) {
                    f0 = f->next;
                }
                
                del_clause(&f);
                cc--;
                go_next = false;
                break;
            }

            if (c->l == -x) {
                c0 = del_literal(c0, -x);
                f->c = c0;
                break;
            }

            c = c->next;
        }

        if (go_next) {
            f = f->next;
        }
    }

    formula->f = f0;
    formula->varc = varc - 1;
    formula->cc = cc;

}

//------Contain empty
bool contain_empty(CNF* formula) {
    /*Check if there is an empty clause in `formula`.*/

    struct CNF_clause* f = formula->f;

    while (f != NULL) {
        if (f->c == NULL) {
            return true;
        }

        f = f->next;
    }

    return false;
}

//------Use solver
void use_solver(CNF* formula, char* algo, char* heur, bool verbose) {
    /*Use quine with formula and print output.*/

    //---Create the valuation array
    int n = formula->varc;
    int* val = (int*) malloc(n * sizeof(int));
    for (int k = 0 ; k < n ; k++) {
        val[k] = -1;
    }

    //---run solver
    clock_t t = clock();
    bool sat;

    if (strcmp(algo, "quine") == 0)
        sat = quine(formula, &val, n);
    else //DPLL algo, the wrong string case is handled in parse function.
        sat = dpll(formula, heur, &val, n);

    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC;

    //---Display result
    if (sat) {
        printf("SATISFIABLE\n");

        if (verbose) {
            for (int k = 0 ; k < n ; k++) {
                if (val[k] == 0)
                    printf("v -%d\n", k + 1);
                else
                    printf("v %d\n", k + 1);
            }

            printf("\nElapsed time : %lf sec\n", time_taken);
        }
        else {
            for (int k = 0 ; k < n ; k++) {
                if (val[k] == 0)
                    printf("-%d ", k + 1);
                else
                    printf("%d ", k + 1);
            }
            printf("\n");
        }
    }
    else {
        printf("UNSATISFIABLE\n");

        if (verbose) {
            printf("\nElapsed time : %lf sec\n", time_taken);
        }
    }

    free(val);
}