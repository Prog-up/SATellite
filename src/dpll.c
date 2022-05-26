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
#include "../include/dpll.h"

//------Functions
//---Unit propagate
CNF* unit_propagate(CNF* formula, int** val) {
    /*
    Search for all unit clauses, and propagate them,
    i.e evaluate `formula` for all the variables that
    appears in such clauses.

    Input :
        - formula : the formula in which propagate unit clauses ;
        - val     : the array representing the partial valuation of variables.
    
    Output :
        A copy of `formula` where all variables appearing in unit clauses are removed.
    */

    CNF* f_cpy = copy_CNF(formula);

    //int cc = f_cpy->cc;
    //int varc = f_cpy->varc;

    struct CNF_clause* f = f_cpy->f;
    //struct CNF_clause* f0 = f; //head

    while (f != NULL) {
        Clause c = f->c;
        
        if (clause_size(c) == 1) {
            int l = c->l;
            int x;

            if (l < 0) {
                x = -l;
                (*val)[x - 1] = 0;
            }
            else {
                x = l;
                (*val)[x - 1] = 1;
            }
            eval(f_cpy, x, (*val)[x - 1]);
        }

        f = f->next;
    }

    return f_cpy; //TODO: Test this function
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
}