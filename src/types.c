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
        q = c;

    }

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
        q = cl;

    }

    return cl;
}


//------Deleting functions
Clause del_literal(Clause c, int x) {
    /*Remove all occurences of `x` in the clause c.*/

    if (c == NULL)
        return c;
    
    if (c->l == x) {
        Clause t = c;
        c = t->next;
        free(t);
        return del_literal(c, x);
    }

    c->next = del_literal(c->next, x);

    return c;
}

struct CNF_clause* del_clause(struct CNF_clause* f) {
    /*Return f with the first clause removed*/

    if (f == NULL) {
        return NULL;
    }

    struct CNF_clause* ret = f->next;

    free_clause(f->c);
    free(f);

    return ret;
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
    /*Return a copy of c, but swap order.*/

    Clause cp = NULL;

    while (c != NULL) {
        Clause lit = (Clause) malloc(sizeof(struct literal));
        lit->l = c->l;
        lit->next = cp;
        cp = lit;

        c = c->next;
    }

    return cp;
}

Clause copy_clause(Clause c) {
    /*Return a copy of `c`.*/

    Clause c0 = copy_clause_0(c);
    Clause c1 = copy_clause_0(c0);

    free_clause(c0);

    return c1;
}

//---Copy CNF
CNF* copy_CNF_0(CNF* formula) {
    /*Return a copy of `formula`, but swap order.*/

    struct CNF_clause* f = formula->f;
    struct CNF_clause* f0 = NULL;

    while (f != NULL) {
        struct CNF_clause* cl = (struct CNF_clause*) malloc(sizeof(struct CNF_clause));
        cl->c = copy_clause(f->c);
        cl->next = f0;
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

    CNF* f0 = copy_CNF_0(formula);
    CNF* f1 = copy_CNF_0(f0);

    free_CNF(f0);

    return f1;
}

//------Eval
CNF* eval(CNF* formula, int x, bool v) {
    /*
    Evaluate the formula at x with value v.
    
    Input :
        - formula : the CNF* formula ;
        - x       : the variable ;
        - v       : the value that should take the variable.
    
    Output :
        the formula, where all clause where there is `x` are removed, and where -`x` is removed from all clauses.
    */

    CNF* f_cpy = copy_CNF(formula);

    struct CNF_clause* f = f_cpy->f;
    struct CNF_clause* f0 = f;

    if (f == NULL) {
        return f_cpy;
    }

    while (f->next != NULL) {
        Clause c = f->next->c;

        bool go_next = true;
        while (c != NULL) {
            if (c->l == x) {
                //f = del_clause(f); //TODO: link f and f->next->next

                /* struct CNF_clause* t = f->next;
                f->next = f->next->next;
                free_clause(t->c);
                free(t); */

                //TODO: There is a segfault somewhere here, maybe try with f->next and the above thing to remove a clause from the clause list.


                /* print_CNF_clause_lst(f);
                printf("---\n"); */
                f_cpy->cc--;
                go_next = false;
                break;
            }

            if (c->l == -x) {
                c = del_literal(c, -x);
            }

            c = c->next;

            print_CNF_clause_lst(f0);
        }

        if (go_next)
            f = f->next;
    }

    f_cpy->f = f0;
    f_cpy->varc--;

    return f_cpy;

}