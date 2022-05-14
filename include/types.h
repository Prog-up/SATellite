#ifndef TYPES_H
#define TYPES_H

//---Literal list
struct literal {
    int l;
    struct literal* next;
};
typedef struct literal* Clause;

//---Clause list
struct CNF_clause {
    Clause c;
    struct CNF_clause* next;
};

typedef struct {
    struct CNF_clause* f; //Formula
    int cc;               //Clause count
    int varc;             //Variables count
} CNF;

//---Functions from `types.c`
//CNF* create_CNF(int size);
Clause arr_to_Clause(int* arr, int n);
struct CNF_clause* Clause_arr_to_CNF_clause(Clause* arr, int n);

#endif