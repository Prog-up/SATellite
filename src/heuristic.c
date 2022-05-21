//------------------------------
// Heuristics
//------------------------------

//---Includes
#include <stdlib.h>
#include "../include/types.h"

//---Heuristic by frequency
int** heuristic_freq(CNF* formula){ //tabular of the most used literals
    int** res = (int*) malloc ((formula->varc) *sizeof (int));
    for (int i=0; i<formula->varc; i++){
        *res[i] = 0;
    } // all the cases of res equal to 0
    struct CNF_clause* c = formula->f;
    while (c->next != NULL){ // parcours of clauses
        Clause l = c->c;
        while (l->next != NULL){ // parcours of literals
            *res[l->l] = *res[l->l]++;
            l = l->next;
        }
        c = c->next;
    }
}