# Satellite
Satellite is a SAT-solver.

<img src="Style/satellite_white_surround.png" alt="Satellite_logo" width="300"/>

## Installing
### Linux
Download the project, go to project's root, and run the file `build.sh` :
```bash
chmod u+x build.sh
./build.sh
```

Note : you need to have `gcc` installed on your computer.

### Windows
Download the project, go to project's root, and execute the file `build.sh` with `Cygwin`.

Note : you need to have [Cygwin](https://www.cygwin.com) (or an equivalent) installed with `gcc` on your computer.

### Running
Once compiled, go to the folder `build`, open a terminal, and you can use the executable `SATellite` (or `SATellite.exe` on windows).

## Usage
### Command line arguments
```
./SATellite -h
Usage : ./SATellite [-h] [-v] [-d] [-a ALGO] [-H HEUR] FILE

Display the satisfiability the input formula, and if it is, print a model of it.

Positional arguments :
    FILE                         Path to a cnf formula encoded in DIMACS format

Optional arguments :
    -h, --help                   Show this help message and exit
    -V, --version                Show version and exit
    -t, --test                   Launch tests
    -d, --display                Print the formula to the screen and exit
    -v, --verbose                Be more verbose
    -a ALGO, --algorithm ALGO    Select solver algorithm. Default is 'quine'
        'quine'
        'dpll'
        
    -H HEUR, --heuristic HEUR    Select an heuristic for DPLL algorithm.
        'first'                  Ignored if ALGO is not 'dpll'.
        'random'
        'freq'
        'jw'
        'jw2'
                                 
```

### Heuristic description
- `first` : select the first literal that is in the formula ;
- `random` : select randomly a literal ;
- `freq` : select the most frequent literal to build a model ;
- `jw` : Jeroslow-Wang one-sided heuristic (select according to a score)
- `jw2` : Jeroslow-Wang two-sided heuristic (select according to a score)

#### Jeroslow-Wang heuristic
let $F$ be the CNF formula
$$F = \bigwedge_{i = 1}^n c_i \quad \text{where} \quad \forall i \in \llbracket 1 ; n \rrbracket,\ c_i = \bigvee_{j = 1}^{m_i} l_{i,j}$$

and where $l_{i,j} = \pm x_{i, j}$ are the literals (and $x_{i,j}$ the variables).

For each literal $l$ (resp. variable $x$ for the two-sided version), calculate $J(l)$ (resp. $J(x)$) :
$$J(l) = \sum_{\substack{c \in F \\ l \in c}} 2^{-|c|}$$

Then choose the literal $l$ (resp. variable) which has the maximum $J(l)$.


### Output description
If the input formula is unsatisfiable, the program outputs
```
UNSATISFIABLE
```

Otherwise, the program outputs `SATSIFIABLE`, with a model below for each variable, *e.g* :

```
SATISFIABLE
1 -2 3 4 -5 ...
```
(x_1 = true, x_2 = false, x_3 = true, ...)

If the flag `-v` / `--verbose` is used, it use a line to show each variable value, and print the elapsed time, *e.g* :

```
SATISFIABLE
v 1
v -2
v 3
...

time elapsed : 0.03s
```

## Implementation choices
### Data structure

We represent the literals as integer (positive for a variable, negative for its negation).

To represent formulae under cnf, we use two nested double chained lists, surrounded by a struct :
- `Clause` : a litteral list ;
- `CNF` : a struct containing a `Clause` list, the clause count, and the variable count.


## Authors
- [Louis TG](https://github.com/lasercata)
- [Enzo J](https://github.com/Prog-up)
- [Câline F](https://github.com/Naory03)

## Licence
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
