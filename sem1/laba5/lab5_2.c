#include <stdio.h>

void main() 
{
    int a;
    int cnt = 0;
    printf("Введите число: ");
    scanf("%d", &a);
    for (int i = 3; i >= 0; i--) {
        if (a & (1<<i)) {printf("1");}
        else {printf("0"); cnt = cnt + 1;}}
    if (cnt >= 4) printf("\n%d кратно 16\n", a);
    else printf("\n%d не кратно 16\n", a);
}
