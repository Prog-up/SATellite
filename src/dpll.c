//------------------------------
// DPLL Algorithm implementation
//------------------------------

//------Includes
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../include/general.h"
#include "../include/types.h"
#include "../include/heuristics.h"
#include "../include/dpll.h"

//------Functions
//---Unit propagate
void unit_propagate(CNF* formula, int** val) {
    /*
    Search for all unit clauses, and propagate them,
    i.e evaluate `formula` for all the variables that
    appears in such clauses.
    It modifies the formula given in input.

    Input :
        - formula : the formula in which propagate unit clauses ;
        - val     : the array representing the partial valuation of variables.
    */

    //CNF* f_cpy = copy_CNF(formula);

    struct CNF_clause* f = formula->f;

    while (f != NULL) {
        Clause c = f->c;
        
        if (clause_size(c) == 1) {
            int l = c->l;

            if (l < 0) {
                (*val)[abs(l) - 1] = 0;
            }
            else {
                (*val)[abs(l) - 1] = 1;
            }
            eval(formula, l, true);
        }

        f = f->next;
    }

    //return f_cpy;
    //TODO: Test this function
}


//---DPLL
bool dpll(CNF* formula, char* heur, int** val, int n) {
    /*
    DPLL algorithm.
    
    - formula : the CNF* formula to try solving ;
    - heur    : the heuristic name ;
    - val     : a pointer to an int array representing the values of the variables. It should first be filled with -1 ;
    - n       : the size of the array `val`. 
    */

    //print_CNF(formula);
    //printf("Unit prop :\n");

    unit_propagate(formula, val);

    //print_CNF(formula);
    //printf("---\n");


    if (formula->f == NULL) {
        return true;
    }
    else if (contain_empty(formula)) {
        return false;
    }
    else {
        int x = next_lit(formula, *val, n, heur);
        //printf("x : %d\n", x);

        CNF* formula2 = copy_CNF(formula);
        eval(formula2, x, true);
        if (dpll(formula2, heur, val, n)) {
            (*val)[abs(x) - 1] = true;
            free_CNF(formula2);
            return true;
        }
        else {
            //free_CNF(formula2);

            CNF* formula3 = copy_CNF(formula);
            eval(formula3, x, false);

            if (dpll(formula3, heur, val, n)) {
                (*val)[abs(x) - 1] = false;
                free_CNF(formula3);
                return true;
            }
            else {
                //free_CNF(formula3);
                return false;
            }
        }
    }
}