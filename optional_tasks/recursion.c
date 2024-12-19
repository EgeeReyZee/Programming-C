#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double logarithm(double x, double n, int i) {
    double y = ((pow((x - 1), (2 * i + 1)))) / ((2 * i + 1) * pow((x + 1), (2 * i + 1)));
    if (y > 0.0001) {  
        n = n + y;
        return logarithm(x, n, i + 1);
    } 
    else {
        return n;
    }
}

int main() {
    int i = 0;
    double x;
    double n = 0;
    printf("Введите аргумент функции: ");
    scanf("%lf", &x);
    double ans = logarithm(x, n, i);
    printf("Ответ: %lf\n", 2 * ans);
    return 0;
}
