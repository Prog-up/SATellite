#ifndef HEUR_H
#define HEUR_H

//------Includes
#include "types.h"

//------Heuristics
int first_h(CNF* formula);
int freq_h(CNF* formula, int n);
int random_h(int* val, int n);
int JeroslowWang_h(CNF* formula, int n, bool two_sided);

//------Next literal
int next_lit(CNF* formula, int* val, int n, char* heur);

#endif