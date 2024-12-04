#include "det.h"

void main() {

    int n;

    printf("Введите размер матрицы(NxN): \n");
    scanf("%d", &n);

    double *determins = (double *)malloc(n*sizeof(double));
    double *ans = (double *)malloc(n*sizeof(double));
    printf("Введите правую часть уравнений\n");
    for (int i = 0; i < n; i++) {
        scanf("%Lf", &ans[i]);
    }
    double **matrix = (double **)malloc(n*sizeof(double));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }
    double **cpmatrix = (double **)malloc(n*sizeof(double));
    for (int i = 0; i < n; i++) {
        cpmatrix[i] = (double *)malloc(n * sizeof(double));
    }

    printf("Введите коэффиценты при переменных слева\n");
    for(int i=0; i < n; i++) {
        for(int j=0; j < n; j++) {
            scanf("%Lf", &matrix[i][j]);
            cpmatrix[i][j] = matrix[i][j];
        }
    }

    double dopdet(double **cpmatrix, int i) {
        for(int i=0; i < n; i++) {
            for(int j=0; j < n; j++) {
                cpmatrix[i][j] = matrix[i][j];
            }
        }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k ++) {
                cpmatrix[j][i] = ans[j];
            }
        }
        determins[i] = det(cpmatrix, n);

    }
    for (int i = 0; i < n; i++) {
        dopdet(cpmatrix, i);
    }
    double detmain = det(matrix, n);
    printf("определитель матрицы равен: %.0Lf\n", detmain);

    for (int i = 0; i < n; i++) {
        printf("x%d = %Lf ", i+1, determins[i]/detmain);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(ans);
    free(determins);
    for (int i = 0; i < n; i++) {
        free(cpmatrix[i]);
    }
    free(cpmatrix);
}