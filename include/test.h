#ifndef TEST_H
#define TEST_H

//------Includes
#include "types.h"

//------Functions
bool check_model(CNF* formula, int* val);
bool test_formula(char* fn, bool expected, char* algo, char* heur);
bool test_dir(char* dirname, bool expected, char* algo, char* heur);
bool test_all();

#endif