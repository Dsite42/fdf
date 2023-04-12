#include <stdio.h>

void printArray(int arr[][rows], int rows) {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<3; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int data[2][3] = { {1, 2, 3}, {4, 5, 6} };
    printArray(data, 2);
    return 0;
}
