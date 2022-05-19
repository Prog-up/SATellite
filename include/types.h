#ifndef TYPES_H
#define TYPES_H

//------Includes
#include <stdbool.h>

//------Data structure
//---Literal list
struct literal {
    int l;
    struct literal* next;
    struct literal* prev;
};
typedef struct literal* Clause;

//---Clause list
struct CNF_clause {
    Clause c;
    struct CNF_clause* next;
    struct CNF_clause* prev;
};

typedef struct {
    struct CNF_clause* f; //Formula
    int cc;               //Clause count
    int varc;             //Variables count
} CNF;

//------Functions from `types.c`
//---Converting functions
Clause arr_to_Clause(int* arr, int n);
struct CNF_clause* Clause_arr_to_CNF_clause(Clause* arr, int n);

//---Deleting functions
Clause del_literal(Clause c, int x);
void del_clause(struct CNF_clause** f);

//---Print
void print_Clause(Clause c);
void print_CNF(CNF* f);
void print_CNF_clause_lst(struct CNF_clause* f0);

//---Free
void free_clause(Clause c);
void free_clause_list(struct CNF_clause* f0);
void free_CNF(CNF* f);

//---Copy
Clause copy_clause(Clause c);
CNF* copy_CNF(CNF* formula);

//---Eval
CNF* eval(CNF* formula, int x, bool v);

#endif