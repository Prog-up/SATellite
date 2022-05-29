//------------------------------
// Tests
//------------------------------

//---Include
#include <dirent.h> 
#include <stdio.h> 
#include <string.h>


//---Print name of cnf files
void print_cnf_files(){
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
        if(strstr(dir->d_name, ".cnf")){ // check if files names contains ".cnf"
            printf("%s\n", dir->d_name);
        }
    }
    closedir(d);
  }
}

bool sat_test (char d_name) {
  if (dpll(dir->d_name) = TRUE) return TRUE ;
  else if (quine(dir->d_name) = TRUE) return TRUE ;
  else return false ; // the formula is unsatisfiable
}



//---TMP
int main(void){
    print_cnf_files();
    return 0;
}
