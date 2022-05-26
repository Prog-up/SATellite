#ifndef HEUR_H
#define HEUR_H

//------Includes
#include "types.h"

//------Heuristics
int first_h(CNF* formula);
int freq_h(CNF* formula);
int random_h(CNF* formula, int* val);
int JeroslowWang1_h(CNF* formula);
int JeroslowWang2_h(CNF* formula);

#endif