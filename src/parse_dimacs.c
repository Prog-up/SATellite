//------------------------------
// Parse files in DIMACS format
//------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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
        printf("SATellite: parse_dimacs: Error while opening file '%s'\n", fn);
        perror(fn);
        return NULL;
    }
    
    //------First, search for description line, of the form 'p cnf V C'
    //---Go to 'p'
    char c;
    c = getc(file);
    while (c != 'p') { // Skip all comments and search 'p'
        c = getc(file); //getc reads one char

        if (c == EOF) {
            printf("SATellite: parse_dimacs: File '%s' is not representing a formula under cnf (there is no 'p').\n", fn);
            return NULL;
        }
    }

    //---Check if it is a cnf file
    char buff[255];
    fscanf(file, "%s", buff);
    if (strcmp("cnf", buff) != 0) {
        printf("SATellite: parse_dimacs: File '%s' is not representing a formula under cnf.\n", fn);
        return NULL;
    }

    //---Read variables
    int nb_var, nb_c; // Variables and clauses count.
    fscanf(file, "%d%d", &nb_var, &nb_c);

    //---Create the formula
    //CNF* formula = create_CNF(nb_c);
    //formula->varc = nb_var;

    //struct CNF_clause* f = formula->f;


    //------Read the formula
    char fst; //To test if there is a comment
    int t, nb; //t : temp var for numbers, nb : number of literals in this clause
    int lit_list[nb_var]; //temp clause, there is at max `nb_var`s literals in each clause.

    Clause cl_list[nb_c]; //temp clause arr, converted after to a CNF.

    for (int k = 0 ; k < nb_c ; k++) {
        //---Check if there is not comment
        fst = fgetc(file);
        while (fst == '\n') {
            fst = fgetc(file);
        }

        if (fst == 'c') {
            //Remove the line
            char garbage = fgetc(file);
            while (garbage != '\n') {
                garbage = fgetc(file);
            }
            k--;
            continue; //go to the next iteration of the loop, this line is a comment.
        }
        else {
            t = (int) fst - '0';
        }

        //---Add var to temporary clause array
        nb = 0;
        while (t != 0) {
            lit_list[nb] = t;
            nb++;
            fscanf(file, "%d", &t);
        }

        Clause cl = arr_to_Clause(lit_list, nb);
        //f->c = cl;
        //f = f->next;
        cl_list[k] = cl;
    }

    struct CNF_clause* f2 = Clause_arr_to_CNF_clause(cl_list, nb_c);

    CNF* formula = (CNF*) malloc(sizeof(CNF));
    formula->f = f2;
    formula->cc = nb_c;
    formula->varc = nb_var;

    fclose(file);

    return formula;
}


/* void print_CNF(CNF* f) {
    /*Print a formula represented by `f`.* /
    
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
    /*Free a CNF struct.* /

    for (int k = 0 ; k < f->cc ; k++) {
        free(f->clause_list[k].literals);
    }

    free(f->clause_list);
    free(f);
} */