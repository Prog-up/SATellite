#include <stdbool.h>
#include <stdlib.h>
#include "../include/types.h"

bool quine(CNF c, int n){
    if ((c->varc)=0){
        return true;
    }else{
        CNF c0 = c;
        for (int i=0, i<=(c->varc),i++){ // count varc
            for (int j=0, j<=c->cc, j++){ // count cc
                if (c->next) = NULL{
                    c = c0;
                }else{
                    c = c->next;
                }
                clause lit1 = c->clause_list;
                if (lit1->literals) < 0{
                    del(lit1, lit1->literals);
                    lit1->n = (lit1->n)-1;
                }else{ // suppr clause
                    for (int lit2=0, lit2 <= varc, lit2++){
                        del(c, lit2);
                        lit1->n = 0;
                    }
                }
            }
        c->varc--;           
        }
    return (c->varc = 0);
    }
}