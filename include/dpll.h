#ifndef DPLL_H
#define DPLL_H

//------Includes
#include "types.h"

//------Functions
CNF* unit_propagate(CNF* formula, int** val);
bool dpll(CNF* formula, char* heur, int** val, int n);

#endif