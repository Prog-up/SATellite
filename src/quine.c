//Temporaly location
// n = clause lenght of f = cc or varc?
bool quine(CNF f, int n) {
    if (f[0] = []){
        return true;
    } else {
        for (int i = 0 ; i <= n ; i++) {
            if (f[i] = []) {
                return false;
            }
        }
        // res1 and res2 need to be calculated, but it's to late, I need to sleep :(
        if (quine(res1)) {
            return true;
        } else {
            return quine(res2)
        }
    }
};