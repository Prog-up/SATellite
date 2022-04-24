//------------------------------
// Defining the types used in
// the project.
//------------------------------

typedef struct {
    int* literals;
    int n;
} clause;

typedef struct {
    clause* clause_list;
    int cc; //clauses count
    int varc; //variables count
} CNF;