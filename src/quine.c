//------------------------------
// Quine Algo
//------------------------------

//---Includes
#include <stdbool.h>
#include <stdlib.h>
#include "../include/types.h"

//---Check if there is an empty clause in CNF
bool contain_empty(CNF* formula){
    struct CNF_clause* c = formula->f;
    for(int i=0;i<formula->cc;i++){
        if(c->c=NULL){
            return true;
        }
        c = c->next;
    }
    return false;
}

//---Quine Algo
bool quine(CNF* formula, bool** val){
    if(formula->f = NULL){
        return true;
    }else if (contain_empty(formula->f))
    {
        return false;
    }else{
        int x;
        for (int i=0; i<formula->varc;i++){
            if(val[i]=-1){
                x=i+1;
                break;
            }
        }
        val[x]=1;
        //CNF* formula2 = eval(formula, x, true):
        if(quine(eval(formula, x, true), val)){
            return true;
        }
        val[i]=0;
        //CNF* formula3 = eval(formula, x, false);
        return quine(eval(formula, x, false), val);

    }
}