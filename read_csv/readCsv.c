#include "../jk_resample.h"

#define MAX_LINE_SIZE 1024 // assume max 1024 characters per line

double*** extractData(char *fileName, int n, int T) {
    int maxCols = n * T; // consequence of csv structure

    // malloc 3d array, equivilent to: "double data[n][T][2];"
    double*** data = malloc(n * sizeof(double**)); // rows = subjects
    for (int i = 0; i < n; i++) {
        data[i] = malloc(T * sizeof(double*)); // columns = trial
        for (int j = 0; j < T; j++) {
            data[i][j] = malloc(2 * sizeof(double)); // depth is x or y value
        }
    }

    // open file
    FILE *dataFile = fopen(fileName, "r");
    if (dataFile == NULL) {
        printf("Error openning file.\n");
        exit(1);
    }

    char currLine[MAX_LINE_SIZE]; // output buffer temperarily into string
    char *doubleCharPointer;
    fgets(currLine, sizeof(currLine), dataFile); // throw away header
    for (int i = 1; i < maxCols + 1; i++) { // start after header, and finish 1 later
        fgets(currLine, sizeof(currLine), dataFile); // read current line and put into currLine

        int subj = (i - 1) % n; // based on structure of csv
        int trial = (i - 1) / n; // floor division

        strtok(currLine, ","); // read each element in line as splitted by commas
        char *elem = strtok(NULL, ","); // get x

        data[subj][trial][0] = strtod(elem, &doubleCharPointer);
        // todo: handle for error by checking double char pointer

        elem = strtok(NULL, ","); // get y
        data[subj][trial][1] = strtod(elem, &doubleCharPointer);
    }

    if (fclose(dataFile) != 0) {
        fprintf(stderr, "error closing csv file\n");
    }

    return data;
}

void free3dArray(double*** array, int height, int length) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);
}


void print3dArray(double*** array, int height, int length, int depth) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            for (int k = 0; k < depth; k++) {
                printf("array[%d][%d][%d] = %f\n", i, j, k, array[i][j][k]);
            }
        }
    }
}

int main() {
    // practice with small data
    int n = 18;
    int T = 72;
    char* fileName = "../place_csv_here/test_data_large_18x72.csv";

    double*** tensor = extractData(fileName, n, T);
    print3dArray(tensor, n, T, 2);
    free3dArray(tensor, n, T);
}
// be aware of 0 indexing; subject 2 is read as subject 1.