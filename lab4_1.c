#include <stdio.h>

void main() {
	int a,n,p,d,l,z;
	scanf("%d", &a);
	z = a;
	for(n=0; n != a; n++) {
		p = z;
		while(p > 1) {
		printf("  ");
		p = p - 1;
		}
		l = n;
		while(l > 0) {
		d = '@' + l;
		printf("%c ", d);
		l = l - 1;
		}
		d = 'B';
		while(d < 'A' + n) {
		printf("%c ", d);
		d = d + 1;
		}
		printf("\n");
		z = z - 1;
	}
}
