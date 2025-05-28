#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    srand(time(NULL));
    int k = rand() % 20;
    int a[k];
    int b[k];
    int c[k];
    int maxA = 0;
    int cntB = 0;
    float avgC = 0;
    for(int i=0; i <= k; i++) {
        a[i] = rand() % 50;
        b[i] = (rand() % 50) + 50;
        c[i] = a[i] + b[i];
        if ((i%2==0) && (maxA < a[i])){
            maxA = a[i];
        }
        if ((i%2!=0) && (b[i] < 0)) cntB++;
        avgC = avgC + c[i];
    }
    printf("Максимальная реальная часть числа из массива a = %d\n", maxA);
    printf("Количество отрицательных мнимых частей массива b = %d\n", cntB);
    printf("Среднее арифметическое среди всех элементов массива c = %f\n", avgC/k);
    // printf("c[%d]=[", k);
    // for(int i = 0; i <= k; i++) {
    //     if (i<k) {
    //         printf("%d, ", c[i]);}
    //     else printf("%d", c[i]);
    // }
    // printf("]\n");
}
