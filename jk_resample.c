#include "jk_resample.h"

#define FILE_NAME "place_csv_here/test_data_small_3x2.csv"
#define N 3 // number of subjects
#define T 2 // number of trials for each subject
#define D 2 // number of elements to delete at a time

typedef struct{
    double am1, am2, am3, am4, bm1, bm2, bm3, bm4;
    // alpha moment 1, 2, 3, 4; beta moment 1, 2, 3, 4
} Moments;



Moments iterateThruCombos(double*** array3D, int n, int t, int d) {
    /*
    // start with list {0, 1, ..., d - 1}
    int* toDelete[d]
    for (int i = 0; i < d; i++) {
        toDelete[i] = i;
    }

    
    // toDelete describes the set of subjects to omit from moment calculation

    */

    // toUse describes the set of subjects to use with moment calculation
    // start with list {0, 1, ..., n - d - 1}
    int* toUse[n - d];
    for (int i = 0; i < n - d; i++) {
        toUse[i] = i;
    }

    int toIncrement = n - d - 1;
    while (toIncrement >= 0) {
        toUse[toIncrement]++; // increment right most element 

        // until it reaches n - 1, then move left and increment until it reaches n - 2
        if (toUse[toIncrement] >= d + toIncrement) {
            // proof:
            // i = number elements finished incrementing
            // toIncrement = n - d - 1 - i -> i = n - d - 1 - toIncrement
            // cap = n - 1 - i  -> sub i -> cap = d + toIncrement
            
            toIncrement--;
        }
        // do this until the left most element = d - 1
        // or equivilently when we begin incrementing stuff past the left of the list


    }

}

int main() {
    int n = 3; 
    int T = 2; 
    double*** data = extractData(FILE_NAME, n, T)

    Moments moments = iterThruCombos(data, n, T, d);

    free3dArray(data, n, T);
    return 0;
}