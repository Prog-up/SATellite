//------------------------------
// Defining the types used in
// the project.
//------------------------------

//---Include
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/types.h"


//---Functions
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


Clause del(Clause c, int x) {
    /*Remove all occurences of `x` in the clause c.*/

    if (c == NULL)
        return c;
    
    if (c->l == x) {
        Clause t = c;
        c = t->next;
        free(t);
        return del(c, x);
    }

    c->next = del(c->next, x);

    return c;
}


void print_CNF(CNF* f) {
    /*Output to stdout the formula.*/

    printf("Clause count : %d\nVariable count : %d\n\n", f->cc, f->varc);
    
    struct CNF_clause* f0 = f->f;

    while (true) {
        if (f0 == NULL)
            return;
        
        Clause c = f0->c;
        printf("(");
        while (true) {
            if (c == NULL)
                break;
            
            if (c->l < 0)
                printf("¬x_%d", c->l);
            else
                printf("x_%d", c->l);
            
            if (c->next != NULL)
                printf(" ∨ "); // \wedge : ∨
            
            c = c->next;
        }

        if (f0->next != NULL)
            printf(")\n∧\n");
        else
            printf(")\n");
        
        f0 = f0->next;
    }
}


void print_Clause(Clause c) {
    while (true) {
        if (c == NULL)
            break;
        else
            printf(" || ");
        
        printf("%d", c->l);

        c = c->next;
    }
    printf("\n");
}


void free_CNF(CNF* f) {
    /*Free a CNF* var.*/

    struct CNF_clause* f0 = f->f;
    Clause c = f0->c;
    Clause c1;
    while (true) {
        if (c == NULL)
            break;

        c1 = c->next;
        free(c);
        c = c1;
    }

    free(f0);

    free(f);
}