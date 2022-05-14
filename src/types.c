//------------------------------
// Defining the types used in
// the project.
//------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "../include/types.h"

/* CNF* create_CNF(int size) {
    /*Return a CNF struct. Allocate every clause. Set `f` and `cc`, but not `varc` in the CNF struct.* /

    struct CNF_clause* f = NULL;
    struct CNF_clause* q = NULL;

    for (int k = 0 ; k < size ; k++) {
        f = (struct CNF_clause*) malloc(sizeof(struct CNF_clause));
        if (f == NULL) {
            printf("SATellite: types: cannot allocate memory (in create_CNF)\n");
            return NULL;
        }

        f->next = q;
        q = f;
    }

    CNF* cnf;
    cnf->f = f;
    cnf->cc = size;

    return cnf;
} */

Clause arr_to_Clause(int* arr, int n) {
    /*
    Convert an int array into a Clause struct.
    
    - arr : the array ;
    - n : the array's size.
    */

    Clause c = NULL;
    Clause q = NULL;

    for (int k = n - 1 ; k >= 0 ; k--) {
        c = (Clause) malloc(sizeof(struct literal));
        if (c == NULL) {
            printf("SATellite: types: cannot allocate memory (in arr_to_Clause)\n");
            return NULL;
        }

        c->l = arr[k];
        c->next = q;
        q = c;

    }

    return c;
}

struct CNF_clause* Clause_arr_to_CNF_clause(Clause* arr, int n) {
    /*
    Convert a Clause array to a struct CNF_clause* list.
    
    - arr : the Clause array ;
    - n : the array's size.
    */

    struct CNF_clause* cl = NULL;
    struct CNF_clause* q = NULL;

    for (int k = n - 1 ; k >= 0 ; k--) {
        cl = (struct CNF_clause*) malloc(sizeof(struct CNF_clause));
        if (cl == NULL) {
            printf("SATellite: types: cannot allocate memory (in Clause_arr_to_CNF_clause)\n");
            return NULL;
        }

        cl->c = arr[k];
        cl->next = q;
        q = cl;

    }

    return cl;
}

//TODO : free_CNF
//TODO : print_CNF