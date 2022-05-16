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


    //------Read the formula
    char fst[255]; //To test if there is a comment
    int t, nb; //t : temp var for numbers, nb : number of literals in this clause
    int lit_list[nb_var]; //temp clause, there is at max `nb_var`s literals in each clause.

    Clause cl_list[nb_c]; //temp clause arr, converted after to a CNF.

    for (int k = 0 ; k < nb_c ; k++) {
        //---Check if there is not comment
        //fst = fgetc(file);
        fscanf(file, "%s", fst);
        while (strcmp(fst, "\n") == 0) {
            //fst = fgetc(file);
            fscanf(file, "%s", fst);
        }

        if (strcmp(fst, "c") == 0) {
            //Remove the line
            char garbage = fgetc(file);
            while (garbage != '\n') {
                garbage = fgetc(file);
            }
            k--;
            continue; //go to the next iteration of the loop, this line is a comment.
        }
        else {
            t = atoi(fst);
        }

        //---Add var to temporary clause array
        nb = 0;
        while (t != 0) {
            lit_list[nb] = t;
            nb++;
            fscanf(file, "%d", &t);
        }

        Clause cl = arr_to_Clause(lit_list, nb);
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