//------------------------------
// Include all files, parse
// command line arguments, and
// execute right functions.
//------------------------------

//---Includes
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/parse_dimacs.h"

//---Ini
char version[] = "v1.0";

//---Tests
void test0(char* fn) { //TODO: Remove this function for final version
    /*Testing parse_dimacs*/
    
    CNF* f = parse_cnf(fn);
    print_CNF(f);
    free_CNF(f);
}

//-Parser
void print_logo() {
    printf("\n                            ^JY55Y?~.             \n                            ^JJJJ?JYG#5.          \n          .                  7PYYPGGJ^J@P         \n        7&&#~                 !YY?^:5@?.&&        \n      ?&#^ 7&&~          ?!   :7!?&B ^@?.@P       \n    ?@#:     !&&!      .&&#&7 J@@^.@P #@ #&       \n    ~&&!       ~#&7    Y@. ^B&@5~  5^ &G @#       \n      ^#&?       Y@G.JP&@?   :G#7        7.       \n        ^B&J   ^B@PB&P^.J@B~...J@&.               \n          :B&5B&#@&5.     5@&GGP?.                \n            .YPB&Y.      .G@.                     \n            .G&?       :G&GP5.                    \n            ^&&!     ^B@@B&P5&G:                  \n             .&@&? ^#&PB@5.   Y&B:                \n            5&5.^B&&!.&@!       J&B^              \n            ~.    .    7&#^       7&#^            \n                         7&#~     !&&^            \n                           !&&! ?&#^              \n                             ~#&B:                \n                               .\n");
}

void print_usage(char* argv0) {
    printf("Usage : %s [-h] [-v] [-a ALGO] [-H HEUR] FILE\n", argv0);
}

void print_help(char* argv0) {
    /*
    Print the help message for the command line parser.
    
    - argv0 : program name (argv[0] in the main function).
    */

    print_logo();

    print_usage(argv0);

    printf("\nShow whatever the input formula is satisfiable, and if so, show a model of it.\n");

    printf("\nPositional arguments :\n");
    printf("    FILE                         Path to a cnf formula encoded in DIMACS format\n");

    printf("\nOptional arguments :\n");
    printf("    -h, --help                   Show this help message and exit\n");
    printf("    -v, --version                Show version and exit\n");
    printf("    -a ALGO, --algorithm ALGO    Select the algorithm used. Default is 'quine'\n");
    printf("        'quine'\n");
    printf("        'dpll'\n");
    printf("\n    -H HEUR, --heuristic HEUR    Select an heuristic for DPLL algorithm.\n");
    printf("        'random'                 Ignored if ALGO is not 'dpll'.\n");
    printf("        'freq'\n");
}


int parse(int argc, char** argv) {
    /*Parse command line arguments and execute associated functions.*/

    char algo[6] = "quine";
    char heur[16];
    char fn[255];

    bool file_is_def = false;
    bool algo_is_def = false;
    bool heur_is_def = false;

    if (argc == 1) { //No arguments
        print_logo();
        print_usage(argv[0]);
        printf("SATellite: error: the following argument is requied: FILE\n");
        return -1;
    }

    for (int k = 1 ; k < argc ; k++) {
        if (strcmp(argv[k], "-h") == 0 || strcmp(argv[k], "--help") == 0) { //Help
            print_help(argv[0]);
            return 0;
        }
        else if (strcmp(argv[k], "-v") == 0 || strcmp(argv[k], "--version") == 0) { //Version
            printf("SATellite version : %s\n", version);
            return 0;
        }
        else if (strcmp(argv[k], "-a") == 0 || strcmp(argv[k], "--algorithm") == 0) { //Algorithm
            if (algo_is_def) {
                printf("SATellite: error: too many arguments (argument -a/--algorithm repeated)\n");
                return -1;
            }

            if (k + 1 >= argc) {
                printf("SATellite: error: argument -a/--algorithm: expected one argument ALGO\n");
                return -1;
            }
            if (strcmp(argv[k + 1], "quine") !=0 && strcmp(argv[k + 1], "dpll") != 0) {
                printf("SATellite: error: argument -a/--algorithm: value should be 'quine' or 'dpll', but '%s' was found\n", argv[k + 1]);
                return -1;
            }

            strcpy(algo, argv[k + 1]);
            k++; // Jump the next value (it is algo).

            algo_is_def = true;
        }
        else if (strcmp(argv[k], "-H") == 0 || strcmp(argv[k], "--heuristic") == 0) { //Heuristic
            if (heur_is_def) {
                printf("SATellite: error: too many arguments (argument -H/--heuristic repeated)\n");
                return -1;
            }
            if (k + 1 >= argc) {
                printf("SATellite: error: argument -H/--heuristic: expected one argument HEUR\n");
                return -1;
            }
            if (strcmp(argv[k + 1], "random") !=0 && strcmp(argv[k + 1], "freq") != 0) { //TODO: update heuristic list
                printf("SATellite: error: argument -H/--heuristic: value should be 'random' or 'freq', but '%s' was found\n", argv[k + 1]); //TODO: also here
                return -1;
            }

            strcpy(heur, argv[k + 1]);
            k++; // Jump the next value (it is heur).

            heur_is_def = true;
        }
        else { //File
            if (file_is_def) {
                printf("SATellite: error: too many arguments\n");
                return -1;
            }
            
            strcpy(fn, argv[k]);

            file_is_def = true;
        }
    }
    
    //TODO: use function according to defined arguments

    //CNF* f = parse_cnf(fn);

    return 0;
}


int main(int argc, char** argv) {
    //test0(argv[1]);

    //---Parser
    return parse(argc, argv);
}