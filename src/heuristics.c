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

void print_arr(double* arr, int n) {
    printf("[");
    for (int k = 0 ; k < n ; k++) {
        printf("%.3lf", arr[k]);

        if (k < n - 1)
            printf(", ");
    }
    printf("]\n");
}

//------Maximum
int max_arr(double* arr, int n) {
    /*
    Return the index of the maximum element of the array.
    
    - arr : the array to find maximum ;
    - n   : the length of the array.
    */

    int index = 0;
    double max = arr[0];

    for (int k = 1 ; k < n ; k++) {
        if (arr[k] > max) {
            max = arr[k];
            index = k;
        }
    }

    return index;
}

//------Heuristics
//---First
int first_h(CNF* formula) {
    return abs(formula->f->c->l);
}


//---Frequency
int freq_h(CNF* formula, int n) {
    /*Return the most frequent variable.*/

    //int* freq = (int*) malloc((formula->varc*2) * sizeof(int));
    int len = 2 * n;
    double freq[len];

    for (int i = 0 ; i < len ; i++) { //Set all values of freq to 0.
        freq[i] = 0;
    }

    struct CNF_clause* c = formula->f;
    while (c->next != NULL){ // Browse clauses
        Clause l = c->c;

        while (l->next != NULL){ // Browse literals
            if(l->l > 0)
                freq[l->l - 1]++;
            else
                freq[l->l + formula->varc - 1]++;
            
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
int random_h(CNF* formula) {
    /*Return a random literal that has not already been used.*/

    struct CNF_clause* f = formula->f;
    int rnd_c = rand() % formula->cc;

    for (int i = 0 ; i < rnd_c ; i++) {
        f = f->next;
    }

    Clause c = f->c;
    int rnd_l = rand() % clause_size(c);

    for(int j = 0 ; j < rnd_l ; j++){
        c = c->next;
    }
    
    return c->l;
}

//---Jeroslow-Wang
int JeroslowWang_h(CNF* formula, int n, bool two_sided) {
    /*
    Jeroslow-Wang heuristic
    
    - formula   : the CNF* formula ;
    - n         : the number of variables in the full formula ;
    - two_sided : indicate if use the two-sided version of JW (true) or not (the one-sided, false).
    */

    int len;

    if (two_sided)
        len = 2 * n;
    else
        len = n;

    //double* scores = (double*) malloc(len * sizeof(double));
    double scores[len];

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
                scores[abs(l->l) - 1] += pow(2, -count);
            }
            else if (l->l > 0) {
                scores[l->l - 1] += pow(2, -count);
            }
            else {
                scores[l->l + (formula->varc) - 1] += pow(2, -count);
            }
            l = l->next; 
        }
        c = c->next;
    }

    int max_i = max_arr(scores, len);
    //free(scores);

    if (max_i > formula->varc)
        max_i = (formula->varc) - max_i;
    
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
        return random_h(formula);

    else if (strcmp(heur, "freq") == 0)
        return freq_h(formula, n);

    else if (strcmp(heur, "jw") == 0)
        return JeroslowWang_h(formula, n, false);

    else
        return JeroslowWang_h(formula, n, true);
}
