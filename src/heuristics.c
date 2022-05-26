//------------------------------
// Heuristics
//------------------------------

//---Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/heuristics.h"

//------Init
int n=1;

//------Maximum
int max_arr(int* arr, int n) {
    /*
    Return the index of the maximum element of the array.
    
    - arr : the array to find maximum ;
    - n   : the length of the array.
    */

    int index = 0, max = arr[0];

    for (int k = 1 ; k < n ; k++) {
        if (arr[k] > max) {
            max = arr[k];
            index = k;
        }
    }

    return index;
}

//------Heuristics
//---First (label order : 1, 2, 3, ...)
int first_h(CNF* formula) { // return the first literal
    /* if (n > 0) {
        n = -n;
    }
    else {
        n = 1 - n;
    }
    return n; */

    return abs(formula->f->c->l);
}
//TODO: or simply return formula->f->c->l (if it exists) ?


//---Frequency
int freq_h(CNF* formula) {
    /*Return the most frequent variable.*/

    //int* freq = (int*) malloc((formula->varc*2) * sizeof(int));
    int len = 2 * formula->varc;
    int freq[len];

    for (int i = 0 ; i < len ; i++) { //Set all values of freq to 0.
        freq[i] = 0;
    }

    struct CNF_clause* c = formula->f;
    while (c->next != NULL){ // Browse clauses
        Clause l = c->c;

        while (l->next != NULL){ // Browse literals
            if(l->l > 0)
                freq[l->l]++;
            else
                freq[l->l + formula->varc]++;
            
            l = l->next; 
        }
        c = c->next;
    }

    int max_i = max_arr(freq, len);

    if (max_i > formula->varc)
        max_i = formula->varc - max_i;
    
    return max_i + 1;
}

//---Random
int random_h(int* val, int n) { // return a random literal
    /*
    Return a random literal that has not already been used.
    
    - val : the array representing the partial valuation ;
    - n   : the length of val.
    */

    while (true) {
        int l = (rand() % n);
        if(val[l] == -1) { //Might not work (with recursive calls, val[l] might have been set in a previous try, but not currently).
            return l;
        }
    }
}

//---Jeroslow-Wang
int JeroslowWang_h(CNF* formula, bool two_sided) {
    /*
    Jeroslow-Wang heuristic
    
    - formula   : the CNF* formula ;
    - two_sided : indicate if use the two-sided version of JW (true) or not (the one-sided, false).
    */

    int len;

    if (two_sided)
        len = 2 * formula->varc;
    else
        len = formula->varc;

    //int* scores = (int*) malloc(t_len * sizeof(int));
    int scores[len];

    for (int i = 0 ; i < len ; i++) { // Set scores values to 0
        scores[i] = 0;
    }

    Clause l;
    int count;
    struct CNF_clause* c = formula->f;

    while (c->next != NULL){ // Browse clauses
        l = c->c;

        count = clause_size(l);
        
        while (l->next != NULL){ // Browse literals
            if (!two_sided) {
                scores[abs(l->l)] += pow(2, -count);
            }
            else if (l->l > 0) {
                scores[l->l] += pow(2, -count);
            }
            else {
                scores[l->l + formula->varc] += pow(2, -count);
            }
            l = l->next; 
        }
        c = c->next;
    }

    int max_i = max_arr(scores, len);

    if (max_i > formula->varc)
        max_i = formula->varc - max_i;
    
    return max_i + 1;
}

//TODO: a function `max`, and use the function `clause_size` from types.h

//------Next lit
int next_lit(CNF* formula, int* val, int n, char* heur) {
    /*
    Return the next literal to use in dpll according to the heuristic `heur`.
    
    - formula : the CNF* formula ;
    - val     : the partial valuation array of formula ;
    - n       : the length of val ;
    - heur    : the heuristic name (defined in main.c/parse).
    */

    if (strcmp(heur, "first") == 0)
        return first_h(formula);

    else if (strcmp(heur, "random") == 0)
        return random_h(val, n);

    else if (strcmp(heur, "freq") == 0)
        return freq_h(formula);

    else if (strcmp(heur, "jw") == 0)
        return JeroslowWang_h(formula, false);

    else
        return JeroslowWang_h(formula, true);
}