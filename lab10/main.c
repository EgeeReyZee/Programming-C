#include "functions.h"

void main() {
    Complex a, b, c;

    printf("Введите числа a, b, c по очереди\n");
    scanf("%lf %lf", &a.x, &a.y);
    scanf("%lf %lf", &b.x, &b.y);
    scanf("%lf %lf", &c.x, &c.y);

    Complex q = calculateQ(a, b, c);

    printf("Q: (%lf, %lf)\n", q.x, q.y);

}
