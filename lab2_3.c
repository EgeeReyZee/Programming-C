#include <stdio.h>
#include <math.h>

void main() {
	float x;
	float y;
	scanf("%f %f", &x, &y);
	if ((x > -2 && x <= 1) && (y > -2 && y <= 0)) {
		printf("YES\n");
	}
	else if ((x > -2 && x < -1) && (y >= 0 && y <= 1)) {
		printf("YES\n");
	}
	else if ((x >= -1 && x <= 0) && (pow(pow(x, 2), 0.5) >= y)) {
		printf("YES\n");
	}
	else
		printf("NO\n");
}
