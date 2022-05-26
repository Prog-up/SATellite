//------------------------------
// Heuristics
//------------------------------

//---Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include "../include/types.h"
#include "../include/parse_dimacs.h"
#include "../include/heuristics.h"

//---Init
int n=1;

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
int random_h(CNF* formula, int* val){ // return a random literal
    while(true){
        int rd=(rand() % formula->varc+1);
        if(val[rd]==-1){
            return val[rd];
        }
    }
}

//---Jeroslow-Wang with difference betwen a literal and it's negation
int JeroslowWang1_h(CNF* formula) {
    /*Jeroslow-Wang one-sided heuristic*/

    Clause l;
    Clause l2;
    int count;
    int* tab = (int*) malloc ((formula->varc*2) *sizeof (int));
    for(int i=0 ; i<formula->varc*2 ; i++){
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
            if(l->l>0){
                tab[l->l]+=pow(2, -count);
            }else{
                tab[l->l+formula->varc]+=pow(2, -count);
            }
            l = l->next; 
        }
        c = c->next;
    }
    int max = 0, res = 0;
    for(int j=0; j<formula->varc*2; j++){ // search the literal with better score
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

//TODO: a function `max`, and use the function `clause_size` from types.h

//---Jeroslow-Wang without difference betwen a literal and it's negation
int JeroslowWang2_h(CNF* formula) {
    /*Jeroslow-Wang two-sided heuristic*/

    Clause l;
    Clause l2;
    int count;
    int* tab = (int*) malloc ((formula->varc) *sizeof (int));
    for(int i=0 ; i<formula->varc ; i++){
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
            tab[abs(l->l)]+=pow(2, -count);
            l = l->next; 
        }
        c = c->next;
    }
    int max = 0, res = 0;
    for(int j=0; j<formula->varc; j++){ // search the literal with better score
        if(tab[j]>max){
            res=j;
            max=tab[j];
        }
    }
    free(tab);
    return res;
}

/* //---Tmp, debug
int main_(void){
    for(int i=0;i<100;i++){
        print_CNF(parse_cnf("../test/SAT.cnf"));
        printf("\n");
        printf("%d", first_h(parse_cnf("../test/SAT.cnf")));
    }
    return 0;
} */