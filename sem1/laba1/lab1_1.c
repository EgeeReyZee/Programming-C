#include <stdio.h>

void main() {
	float a = 619.1;
	float b = 228.2;
	printf("|%f|\n", a);
	printf("|%30f|\n", a);
	printf("|%-30f|\n", a);
	printf("\n");
	printf("Words:       69\n");
	printf("Letters:    119\n");
	printf("Digits:     911\n");
	printf("a = %f", a);
	printf("; b = %f\n", b);
	printf("a + b = %f\n", a+b);
}
