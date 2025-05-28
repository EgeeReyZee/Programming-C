#include <stdio.h>

void main()
{
    int a;
    int cnt = 0;
    printf("Введите число: ");
    scanf("%d", &a);
    for (int i = 12; i >= 2; i--) {
        if (a & (1<<i)) printf("1");
        else { printf("0"); cnt = cnt + 1;}
    }
    printf("\nКоличество нулей в числе c третьего по 13 бит = %d\n", cnt);
}
