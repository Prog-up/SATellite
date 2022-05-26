//------------------------------
// Defining the types used in
// the project.
//------------------------------

//---Include
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/types.h"


//------Converting functions
Clause arr_to_Clause(int* arr, int n) {
    /*
    Convert an int array into a Clause struct.
    
    - arr : the array ;
    - n   : the array's size.
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

        if (q != NULL) {
            q->prev = c;
        }

        q = c;

    }

    c->prev = NULL;

    return c;
}

struct CNF_clause* Clause_arr_to_CNF_clause(Clause* arr, int n) {
    /*
    Convert a Clause array to a struct CNF_clause* list.
    
    - arr : the Clause array ;
    - n   : the array's size.
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

        if (q != NULL) {
            q->prev = cl;
        }

        q = cl;

    }

    cl->prev = NULL;

    return cl;
}


//------Deleting functions
/* Clause del_literal_rec(Clause c, int x) {
    / *Remove all occurences of `x` in the clause c.* /

    printf("del0\n");

    if (c == NULL)
        return NULL;
    
    printf("del1\n");
    
    if (c->l == x) {
        printf("del: c->l == x\n");
        Clause t = c;

        if (c->next == NULL && c->prev != NULL) {
            c->prev->next = NULL;
        }

        c = t->next;

        if (c != NULL) {
            c->prev = t->prev;

            if (c->prev != NULL)
                c->prev->next = c;
        }

        free(t);
        return del_literal(c, x);
    }

    c->next = del_literal(c->next, x);

    return c;
} */

Clause del_literal(Clause c, int x) {
    /*Remove all occurences of `x` in the clause c.*/

    Clause c0 = c;
    
    while (c != NULL) {
        if (c->l == x) {
            Clause t = c;

            if (c == c0)
                c0 = c0->next;

            if (c->next == NULL && c->prev != NULL) {
                c->prev->next = NULL;
            }

            c = t->next;

            if (c != NULL) {
                c->prev = t->prev;

                if (c->prev != NULL)
                    c->prev->next = c;
            }

            //free(t);
        }
        else
            c = c->next;

        //TODO: solve this bug
        if (c != NULL && c == c->next) { //Lazy evaluation
            printf("c == c->next ...\n");
            c->next = NULL;
            c->prev = NULL;
            break;
        }
    }

    return c0;
}


void del_clause(struct CNF_clause** f) {
    /*
    Remove the first clause from *f.
    
    - f : a pointer to a clause list ;
    */

    if (*f == NULL) {
        return;
    }

    struct CNF_clause* t = *f;

    if ((*f)->next == NULL && (*f)->prev != NULL) {
        (*f)->prev->next = NULL;
    }

    (*f) = (*f)->next;

    if (*f != NULL) {
        (*f)->prev = t->prev;

        if ((*f)->prev != NULL)
            (*f)->prev->next = *f;
    }

    //free_clause(t->c);
    //free(t);
}


//------Print
void print_Clause(Clause c) {
    while (c != NULL) {
        printf("%d", c->l);

        if (c->next != NULL)
            printf(" || ");

        c = c->next;
    }
    printf("\n");
}

void print_CNF_clause_lst(struct CNF_clause* f0) {
    /*Print the formula.*/

    while (f0 != NULL) {
        Clause c = f0->c;
        printf("(");
        while (c != NULL) {
            if (c->l < 0)
                printf("¬x_%d", -c->l);
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

void print_CNF(CNF* f) {
    /*Output to stdout the formula.*/

    printf("Clause count : %d\nVariable count : %d\n\n", f->cc, f->varc);
    
    struct CNF_clause* f0 = f->f;

    print_CNF_clause_lst(f0);
}


//------Free
//---Free clause
void free_clause(Clause c) {
    /*Free a Clause list.*/

    Clause c1;

    while (c != NULL) {
        c1 = c->next;
        free(c);
        c = c1;
    }
}

//---Free Clause list
void free_clause_list(struct CNF_clause* f0) {
    /*Free a struct CNF_clause* list.*/

    struct CNF_clause* f1;

    while (f0 != NULL) {
        f1 = f0->next;
        free_clause(f0->c);
        free(f0);
        f0 = f1;
    }
}

//---Free CNF
void free_CNF(CNF* formula) {
    /*Free a CNF* struct.*/

    struct CNF_clause* f = formula->f;
    
    free_clause_list(f);

    free(formula);
}

//------Copy
//---Copy clause
Clause copy_clause_0(Clause c) {
    /*Return a copy of c, but in opposite order.*/

    Clause cp = NULL;
    Clause lit = NULL;

    while (c != NULL) {
        lit = (Clause) malloc(sizeof(struct literal));
        lit->l = c->l;
        lit->next = cp;

        if (cp != NULL) {
            cp->prev = lit;
        }

        cp = lit;

        c = c->next;
    }

    return cp;
}

Clause copy_clause(Clause c) {
    /*Return a copy of `c`.*/

    /* Clause c0 = copy_clause_0(c);
    Clause c1 = copy_clause_0(c0);

    free_clause(c0);

    return c1; */
    return copy_clause_0(c);
}

//---Copy CNF
CNF* copy_CNF_0(CNF* formula) {
    /*Return a copy of `formula`, but in opposite order.*/

    struct CNF_clause* f = formula->f;
    struct CNF_clause* f0 = NULL;

    while (f != NULL) {
        struct CNF_clause* cl = (struct CNF_clause*) malloc(sizeof(struct CNF_clause));
        cl->c = copy_clause(f->c);
        cl->next = f0;

        if (f0 != NULL) {
            f0->prev = cl;
        }

        f0 = cl;

        f = f->next;
    }

    CNF* ret = (CNF*) malloc(sizeof(CNF));
    ret->cc = formula->cc;
    ret->varc = formula->varc;
    ret->f = f0;

    return ret;
}

CNF* copy_CNF(CNF* formula) {
    /*Return a copy of `formula`.*/

    /* CNF* f0 = copy_CNF_0(formula);
    CNF* f1 = copy_CNF_0(f0);

    free_CNF(f0);

    return f1; */
    return copy_CNF_0(formula);
}


//------Clause size
int clause_size(Clause c) {
    /*Return the nuber of elements in the Clause `c`. */

    int n = 0;
    while (c != NULL) {
        n++;
        c = c->next;
    }

    return n;
}