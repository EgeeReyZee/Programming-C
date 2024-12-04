#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fulling(double **matrix, char arg, int n, int m) {

    if (arg == '1') {
        srand(time(NULL));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matrix[i][j] = (rand() % 100) - 50;
                printf("%.0lf ", matrix[i][j]);
            }
            printf("\n");
        }
    }
    else if (arg == '0') {
        printf("Вводите значения элементов матрицы\n");
        for(int i=0; i < n; i++) {
            for(int j=0; j < m; j++) {
                scanf("%lf", &matrix[i][j]);
            }
        }
    }
    else {
        printf("Неверный ввод");
    }
}

void negative_max(double **matrix, int n, int m) {
    int max_row = -1;
    int max_elems = 0;
    int plus = n*m;
    for (int i = 0; i < n; i++) {
        int row_cnt = 0;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < 0) {
                row_cnt++;
                plus--;
            }
        }
        if (row_cnt > max_row) {
            max_elems = row_cnt;
            max_row = i;
        }
    }
    if (plus < n*m) {
        printf("Строка с самым большим количеством отрицательных чисел: ");
        for (int i = 0; i < m; i++) {
            printf("%.0lf ", matrix[max_row][i]);
        }
    }
    else {
        printf("Все числа положительные");
    }
    printf("\n");
}

void neg_plus(double **matrix, int n, int m, int skal) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] < 0) {
                for (int k = 0; k < m; k++) {
                    matrix[i][k] += skal;
                }
                break;
            } 
        }
    }
    printf("Новая матрица\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.0lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void sort(double **matrix, int n, int m) {
    int i = 0;
    int max_row = i;
for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (matrix[j][0] > matrix[j + 1][0]) {
                double *temp = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = temp;
            }
        }
    }
    printf("Отсортированная матрица\n");
    for (int i = n-1; i > -1; i--) {
        for (int j = 0; j < m; j++) {
            printf("%.0lf ", matrix[i][j]);
        }
        printf("\n");
    }

}

int main() {
    int n, m;
    printf("Введите размер матрицы: ");
    scanf("%d %d", &n, &m);
    int skal = n + m;
    double **matrix = (double **)malloc(n*sizeof(double *));
    for (int i = 0; i < m; i++) {
        matrix[i] = (double *)malloc(m*sizeof(double));
    }
    printf("Заполнить матрицу автоматически? (1/0): ");
    char arg;
    scanf(" %c", &arg);
    fulling(matrix, arg, n, m);
    negative_max(matrix, n, m);
    neg_plus(matrix, n, m, skal);
    sort(matrix, n, m);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}