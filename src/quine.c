//------------------------------
// Quine Algorithm
//------------------------------

//---Includes
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/quine.h"

//---Check if there is an empty clause in a CNF
bool contain_empty(CNF* formula) {
    struct CNF_clause* c = formula->f;

    while (c != NULL) {
        if (c->c == NULL) {
            return true;
        }

        c = c->next;
    }

    return false;
}

//---Quine Algo
bool quine(CNF* formula, int** val, int n) {
    /*
    Quine algorithm.
    
    - formula : the CNF* formula to try solving ;
    - val     : a pointer to an int array representing the values of the variables. It should first be filled with -1 ;
    - n       : the size of the array `val`. 
    */

    printf("In quine : 0\n");
    print_CNF(formula);
    printf("-\n");

    if (formula->f == NULL) {
        return true;
    }
    else if (contain_empty(formula)) {
        return false;
    }
    else {
        int x = n - formula->varc + 1;

        CNF* formula2 = eval(formula, x, true);
        if (quine(formula2, val, n)) {
            (*val)[x - 1] = 1;
            return true;
        }

        free_CNF(formula2);

        printf("In quine : before f3, var : %d\n", x);
        printf("---\n");
        print_CNF(formula);
        printf("---\n");
        CNF* formula3 = eval(formula, x, false);
        print_CNF(formula3);
        printf("---\n");
        if (quine(formula3, val, n)) {
            free_CNF(formula3);
            (*val)[x - 1] = 0;
            return true;
        }
    }
}

void use_quine(CNF* formula) {
    /*Use quine with formula and print output.*/

    int n = formula->varc;
    int* val = (int*) malloc(n * sizeof(int));
    for (int k = 0 ; k < n ; k++) {
        val[k] = -1;
    }

    bool sat = quine(formula, &val, n);

    if (sat) {
        printf("SATISFIABLE\n");
        for (int k = 0 ; k < n ; k++) {
            printf("x_%d = %d\n", k + 1, val[k]);
        }
    }
    else
        printf("UNSATISFIABLE\n");

    free(val);
}