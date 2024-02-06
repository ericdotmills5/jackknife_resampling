#include <stdio.h>

void print_combinations(int arr[], int data[], int start, int end, int index, int r) {
    if (index == r) {
        for (int j = 0; j < r; j++)
            printf("%d ", data[j]);
        printf("\n");
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        print_combinations(arr, data, i + 1, end, index + 1, r);
    }
}

void generate_combinations(int arr[], int n, int r) {
    int data[r];
    print_combinations(arr, data, 0, n - 1, 0, r);
}

int main() {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    int r = 16;
    int n = sizeof(arr) / sizeof(arr[0]);
    generate_combinations(arr, n, r);
    return 0;
}