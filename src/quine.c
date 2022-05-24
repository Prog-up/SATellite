//------------------------------
// Quine Algorithm implementation
//------------------------------

//---Includes
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../include/quine.h"
#include "../include/general.h"

//---Check if there is an empty clause in a CNF
bool contain_empty(CNF* formula) {
    struct CNF_clause* f = formula->f;

    while (f != NULL) {
        if (f->c == NULL) {
            return true;
        }

        f = f->next;
    }

    return false;
}

//---Quine Algorithm
bool quine(CNF* formula, int** val, int n) {
    /*
    Quine algorithm.
    
    - formula : the CNF* formula to try solving ;
    - val     : a pointer to an int array representing the values of the variables. It should first be filled with -1 ;
    - n       : the size of the array `val`. 
    */

    if (formula->f == NULL) {
        return true;
    }
    else if (contain_empty(formula)) {
        return false;
    }
    else {
        int x = n - formula->varc + 1;

        CNF* formula2 = copy_CNF(formula);
        eval(formula2, x, true);
        if (quine(formula2, val, n)) {
            (*val)[x - 1] = 1;
            free_CNF(formula2);
            return true;
        }
        else {
            //free_CNF(formula2);

            CNF* formula3 = copy_CNF(formula);
            eval(formula3, x, false);
            if (quine(formula3, val, n)) {
                
                free_CNF(formula3);
                (*val)[x - 1] = 0;
                return true;
            }
            else {
                //free_CNF(formula3);
                return false;
            }
        }
    }
}

void use_quine(CNF* formula, bool verbose) {
    /*Use quine with formula and print output.*/

    int n = formula->varc;
    int* val = (int*) malloc(n * sizeof(int));
    for (int k = 0 ; k < n ; k++) {
        val[k] = -1;
    }

    clock_t t = clock();
    bool sat = quine(formula, &val, n);
    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC;

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