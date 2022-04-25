//------------------------------
// Include all files, parse
// command line arguments, and
// execute right functions.
//------------------------------

//---Includes
#include <stdio.h>
#include <string.h>
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
    printf("\tFILE                         Path to a cnf formula encoded in DIMACS format\n");

    printf("\nOptional arguments :");
    printf("\t-h, --help                   Show this help message and exit\n");
    printf("\t-v, --version                Show version and exit\n");
    printf("\t-a ALGO, --algorithm ALGO    Select the algorithm used. Currently, 'quine'\n                                 and 'dpll' are available. Default is 'quine'.\n");
    printf("\t-H HEUR, --heuristic HEUR    Select an heuristic for DPLL algorithm.\n                                 Currently, 'random', 'freq', ??? are available.\n                                 Ignored if ALGO is not 'dpll'.\n");
}


int parse(int argc, char** argv) {
    /*Parse command line arguments and execute right functions.*/

    if (argc == 1) { //No arguments
        print_logo();
        print_usage(argv[0]);
        printf("SATellite: error: the following argument is requied: FILE\n");
        return 0;
    }

    for (int k = 1 ; k < argc ; k++) {
        if (strcmp(argv[k], "-h") == 0 || strcmp(argv[k], "--help") == 0) { //Help
            print_help(argv[0]);
            return 0;
        }
        else if (strcmp(argv[k], "-v") == 0 || strcmp(argv[k], "--version") == 0) { //Version
            printf("Version : %s\n", version);
            return 0;
        }
        //TODO
    }

    return 0;
}


int main(int argc, char** argv) {
    //test0(argv[1]);

    //---Parser
    return parse(argc, argv);
}