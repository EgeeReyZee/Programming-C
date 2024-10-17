#include <stdio.h>
#include <stdlib.h>

void main()
{
    int k = rand() % 20;
    int X[k];
    int firstPlus = 1000000;
    int lastMinus = 0;
    float avgX = 0;
    int pol;
    for(int i=0; i <= k; i++) {
        X[i] = rand() % 50;
        if ((X[i] > 0) && (firstPlus > i)) {firstPlus = i;}
        if (X[i] < 0) lastMinus = i;
    }
    if (firstPlus < lastMinus) {
        for(int i = firstPlus; i <= lastMinus; i++){
            avgX = avgX + X[i];
        }
        printf("Среднее арифметическое чисел между первым положительным и последним отрицательным = %f\n", avgX/k);
    }
    else printf("В массиве нет отрицательных чисел\n");
    for(int i = 0; i <= k; i++) {
        for (int n=X[i], s=0; n!=0; n=n/10)
	    {pol=n%10; s=s*10+pol;
        if (s == X[i]) {
            X[i] = 0;
            for (int i = s; i < k; i++) {
            X[i] = X[i + 1];
        }
        }
    }
    }
    printf("X[%d]=[", k);
    for(int i = 0; i <= k; i++) {
        if (i<k) {
            printf("%d, ", X[i]);}
        else printf("%d", X[i]);
    }
    printf("]\n");
}