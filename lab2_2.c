#include <stdio.h>

void main()
{
	double t, g;
	char n;

	scanf("%lf %c", &t, &n);
	if (n == 'C' || n == 'c') {
		g = (t*1.8)+32;
		printf("%lf\n", g);
}
	else if (n == 'F' || n == 'f') {
		g = (t-32)/1.8;
		printf("%lf\n", g);
}
	else
		printf("Output error\n");
}

