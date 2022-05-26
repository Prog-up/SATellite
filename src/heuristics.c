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
int max(int a,int b){ //Why ?
    if(a>=b){
        return a;
    }
    return b;
}

//------Heuristics
//---First (label order : 1, 2, 3, ...)
int first_h(CNF* formula) { // return the first literal
    if (n > 0) {
        n = -n;
    }
    else {
        n = 1 - n;
    }
    return n;
} //TODO: or simply return formula->f->c->l (if it exists) ?


//---Frequency
int freq_h(CNF* formula) { //tabular of the most used literals
    int* tab = (int*) malloc ((formula->varc*2) *sizeof (int));
    for(int i=0 ; i<formula->varc*2 ; i++){
        tab[i] = 0;
    } // all the cases of tab equal to 0
    struct CNF_clause* c = formula->f;
    while (c->next != NULL){ // parcours of clauses
        Clause l = c->c;
        while (l->next != NULL){ // parcours of literals
            if(l->l>0){
                tab[l->l]++;
            }else{
                tab[l->l+formula->varc]++;
            }
            l = l->next; 
        }
        c = c->next;
    }
    int max = 0, res = 0;
    for(int j=0; j<formula->varc*2; j++){ // search the most used literal 
        if(tab[j]>max){
            if(j<formula->varc){
                res=j;
            }else{
                res=-(j-formula->varc);
            }
            max=tab[j];
        }
    }
    free(tab);
    return res;
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
        if(val[l] == -1) { //Might not work
            return l;
        }
    }
}

//---Jeroslow-Wang with difference betwen a literal and it's negation
int JeroslowWang_h(CNF* formula, bool diff_neg) {
    /*Jeroslow-Wang one-sided heuristic*/

    Clause l;
    Clause l2;
    int count;
    int x;
    if(diff_neg){
        x = 2;
    }else{
        x = 1;
    }
    int* tab = (int*) malloc ((formula->varc*x) *sizeof (int));
    for(int i=0 ; i<formula->varc*x ; i++){
        tab[i] = 0;
    } // all the cases of tab equal to 0
    struct CNF_clause* c = formula->f;
    while (c->next != NULL){ // parcours of clauses
        l = c->c;

        l2 = c->c; // count of the literals in this clause
        count = 0;
        while (l2->next!=NULL){
            count++;
        }
        
        while (l->next != NULL){ // parcours of literals
            if(!diff_neg){
                tab[abs(l->l)]+=pow(2, -count);
            }else if(l->l>0){
                tab[l->l]+=pow(2, -count);
            }else{
                tab[l->l+formula->varc]+=pow(2, -count);
            }
            l = l->next; 
        }
        c = c->next;
    }
    int max = 0, res = 0;
    for(int j=0; j<formula->varc*x; j++){ // search the literal with better score
        if(tab[j]>max){
            if(!diff_neg || j<formula->varc){
                res=j;
            }else{
                res=-(j-formula->varc);
            }
            max=tab[j];
        }
    }
    free(tab);
    return res;
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
    else if (strcmp(heur, "jw") == 0)  //Fusion 2 JeroslowWang_h with a bool in the conditions
        return JeroslowWang_h(formula, true);
    else //if (strcmp(heur, "jw2") == 0)
        return JeroslowWang_h(formula, false);
}