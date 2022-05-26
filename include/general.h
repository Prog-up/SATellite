#ifndef GENERAL_H
#define GENERAL_H

//------Includes
#include "types.h"

//------Functions
void eval(CNF* formula, int x, bool v);
bool contain_empty(CNF* formula);
void use_solver(CNF* formula, char* algo, char* heur, bool verbose);

#endif