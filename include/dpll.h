#ifndef DPLL_H
#define DPLL_H

//------Includes
#include "types.h"

//------Functions
CNF* unit_propagate(CNF* formula, int** val);

#endif