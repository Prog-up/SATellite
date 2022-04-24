//------------------------------
// Parse files in DIMACS format
//------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parse_dimacs.h"
// #include "../include/types.h" //Already included in header file

CNF* parse_cnf(char* fn) {
    /*
    INPUT :
        - char* fn : path to the DIMACS cnf file.
    
    OUTPUT :
        A pointer to a CNF struct, representing the input file.
        If the file is in a wrong format, it print the error, and return NULL.
    */

    FILE* file = fopen(fn, "r");
    if (file == NULL) {
        printf("Satellite: parse_dimacs: Error while opening file '%s'\n", fn);
        return NULL;
    }
    
    // First, search for description line, of the form 'p cnf V C'
    char c;
    c = getc(file);
    while (c != 'p') { // Skip all comments and search 'p'
        c = getc(file); //getc reads one char
    }

    char buff[255];
    fscanf(file, "%s", buff);
    if (strcmp("cnf", buff) != 0) {
        printf("Satellite: parse_dimacs: File '%s' is not representing a formula under cnf.\n", fn);
        return NULL;
    }

    int nb_var, nb_c; // Variables and clauses count.
    fscanf(file, "%d%d", &nb_var, &nb_c);

    CNF* formula = (CNF*) malloc(sizeof(CNF));
    if (formula == NULL) {
        printf("Satellite: parse_dimacs: cannot allocate memory for `c_list`\n");
        return NULL;
    }
    formula->cc = nb_c;
    formula->varc = nb_var;

    clause* c_list = (clause*) malloc(nb_c * sizeof(clause));
    if (c_list == NULL) {
        printf("Satellite: parse_dimacs: cannot allocate memory for `c_list`\n");
        return NULL;
    }
    formula->clause_list = c_list;

    // Then read all the clauses
    int t, nb; //t : temp var for numbers, nb : number of literals in this clause
    int lit_list[nb_var]; //temp clause, there is at max `nb_var`s literals in each clause.
    for (int k = 0 ; k < nb_c ; k++) {
        nb = 0;
        fscanf(file, "%d", &t);

        while (t != 0) {
            lit_list[nb] = t;
            nb++;
            fscanf(file, "%d", &t);
        }

        clause cl;
        int* lit = (int*) malloc(nb * sizeof(int));
        if (lit == NULL) {
            printf("Satellite: parse_dimacs: cannot allocate memory for `lit` (iteration : k = %d)\n", k);
            return NULL;
        }
        for (int i = 0 ; i < nb ; i++) {
            lit[i] = lit_list[i];
        }

        cl.literals = lit;
        cl.n = nb;

        c_list[k] = cl;
    }

    fclose(file);

    return formula;
}


void print_CNF(CNF* f) {
    /*Print a formula represented by `f`.*/
    
    for (int i = 0 ; i < f->cc ; i++) {
        printf("(");
        for (int j = 0 ; j < f->clause_list[i].n ; j++) {
            if (f->clause_list[i].literals[j] < 0)
                printf("¬x_%d", -(f->clause_list[i].literals[j]));
            else
                printf("x_%d", f->clause_list[i].literals[j]);
            
            if (j != f->clause_list[i].n - 1)
                printf(" ∨ "); // \wedge : ∨
        }

        if (i != f->cc - 1)
            printf(")\n∧\n");
        else
            printf(")\n");
    }
}


void free_CNF(CNF* f) {
    /*Free a CNF struct.*/

    for (int k = 0 ; k < f->cc ; k++) {
        free(f->clause_list[k].literals);
    }

    free(f->clause_list);
    free(f);
}