//------------------------------
// Quine Algorithm implementation
//------------------------------

//---Includes
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/quine.h"
#include "../include/general.h"


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
        //int x = n - formula->varc + 1;
        int x = abs(formula->f->c->l);

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