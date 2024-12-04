#include <stdio.h>
#include <math.h>
#include <stdlib.h>
    
    
double det(double **matrix, int n) {
    double deter = 1.0;
    int i, j, k;

    for (i = 0; i < n; i++) {
        int max_row = i;
        for (k = i + 1; k < n; k++) {
            if (abs(matrix[k][i]) > abs(matrix[max_row][i])) {
                max_row = k;
            }
        }

        if (max_row != i) {
            double *temp = matrix[i];
            matrix[i] = matrix[max_row];
            matrix[max_row] = temp;
            deter *= -1.0;
        }

        if (matrix[i][i] == 0.0) {
            return 0.0;
        }

        for (j = i + 1; j < n; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (k = i; k < n; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    for (i = 0; i < n; i++) {
        deter *= matrix[i][i];
    }

    return deter;
}