#include <stdlib.h>
#include <stdio.h>

void printList(int* list, int len) {
    printf("[");
    for (int i = 0; i < len - 1; i++) {
        printf("%d, ", list[i]);
    }
    printf("%d]\n", list[len - 1]);
}

int main() {
    int n = 18;
    int d = 2;

    int toUse[n - d];
    for (int i = 0; i < n - d - 1; i++) {
        toUse[i] = i;
    }
    toUse[n - d - 1] = n - d - 2; // offset so algorithm starts with correct iteration

    int toIncrement = n - d - 1;
    int i = 0;
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

        // do stuff 

        i++;
        printList(toUse, n - d);
    }
    printf("%d\n", i);

    return 0;
}