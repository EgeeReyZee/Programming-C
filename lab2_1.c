#include <stdio.h>

void main()
{
	int a;
	printf("Enter year: ");
	scanf("%d", &a);
	if (a % 4 == 0)
	{
		if (a % 100 == 0)
		{
			if (a % 400 == 0)
				printf("YES\n");
			else
				printf("NO\n");
		}
		else
			printf("YES\n");
	}
	else
		printf("NO\n");
}
