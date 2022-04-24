# Satellite
Satellite is a SAT-solver.

## Installing
### Linux
Download the project, go to project's root, and run the file `build.sh` :
```bash
./build.sh
```

Note : you need to have `gcc` installed on your computer.

### Windows
Download the project, go to project's root, and execute the file `build.bat`.

Note : you need to have `gcc.exe` installed on your computer, and added to the `PATH` variable.

### Running
Once compiled, go to the folder `build`, open a terminal, and you can use the executable `SATellite` (or `SATellite.exe` on windows).

## Usage
Todo (add parser help)
(explain output)

## Implementation choices
### Data structure

To represent formulae under cnf, we use two nested structures :
- `clause` which represent a clause. It contain an int list (the literal list) and the size of the list ;
- `CNF` which represent the formula. It contain a clause list, the clause count and the variable count.


## Authors
- [Louis TG](https://github.com/lasercata)
- [Enzo J](https://github.com/Prog-up)
- [Câline F](https://github.com/Naory03)

## Licence
Todo