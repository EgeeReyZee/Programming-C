#include <stdio.h>
#include <stdlib.h>

void main() {
    int n;
    printf("Введите размер квадрата: ");
    scanf("%d", &n);
    int **matrix = (int **)malloc(n*sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    int *nums = (int *)malloc(n*n*sizeof(int));
    for (int i = 0; i < n*n; i++) {
        nums[i] = i+10;
        //printf("%d ", nums[i]);
    }
    int temp;
    int num = 1;
    int swap = 0;
    int north = 0;
    int east = n;
    int south = n;
    int west = -1;
    int k = 0;

    while (matrix[n/2][(int)(n/2.0-0.5)] == 0) {
        for (int i = k; i < east; i++) {
            matrix[swap][i] = nums[0];
            temp = i;
            for (int j = 0; j < n*n; j++) {
                nums[j] = nums[j+1];
            }
        }
        east -= 1;
        swap = temp;
        for (int i = k+1; i < south; i++) {
            matrix[i][swap] = nums[0];
            temp = i;
            for (int j = 0; j < n*n; j++) {
                nums[j] = nums[j+1];
            }
        }
        south -= 1;
        swap = temp;
        k += 1;
        for (int i = n-k-1; i > west; i--) {
            matrix[swap][i] = nums[0];
            temp = i;
            for (int j = 0; j < n*n; j++) {
                nums[j] = nums[j+1];
            }
        }
        west += 1;
        swap = temp;
        for (int i = n-k-1; i > north; i--) {
            matrix[i][swap] = nums[0];
            temp = i;
            for (int j = 0; j < n*n; j++) {
                nums[j] = nums[j+1];
            }
        }
        north += 1;
        swap = temp;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}    