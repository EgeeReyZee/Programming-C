#include <stdio.h>

void main() {
	int a = 2147483647;
	char b = -128;
	printf("int max and int max + 1\n");
	printf("a = %d\n", a);
	printf("a + 1 = %d\n", a+1);
	printf("\n");
	printf("char min and char min - 1\n");
	printf("b = %hhd\n", b);
	printf("b - 1 = %hhd\n", b-1);
}
