//------------------------------
// Heuristics
//------------------------------

//---Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/types.h"

//---Init
int n=1;

//---Heuristic by list
int heuristic_first(CNF* formula){ // return the first literal
    if(n>0){
        n=-n;
    }else{
        n=(-n)+1;
    }
    return n;
}

//---Heuristic by frequency
int heuristic_freq(CNF* formula){ //tabular of the most used literals
    int* tab = (int*) malloc ((formula->varc*2) *sizeof (int));
    for(int i=0 ; i<formula->varc ; i++){
        tab[i] = 0;
    } // all the cases of tab equal to 0
    struct CNF_clause* c = formula->f;
    while (c->next != NULL){ // parcours of clauses
        Clause l = c->c;
        while (l->next != NULL){ // parcours of literals
            if(l->l>0){
                tab[l->l] = tab[l->l]++;
            }else{
                tab[l->l+formula->varc] = tab[l->l+formula->varc]++;
            }
            l = l->next; 
        }
        c = c->next;
    }
    int max = 0, res = 0;
    for(int j=0; j<formula->varc; j++){ // search the most used literal 
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

//---Heuristic by random
int heuristic_random(CNF* formula, int* val){ // return a random literal
    while(true){
        int rd=(rand() % formula->varc+1);
        if(val[rd]==-1){
            return val[rd];
        }
    }
}