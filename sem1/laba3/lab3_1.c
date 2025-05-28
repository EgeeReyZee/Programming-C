#include <stdio.h>

void main()
{
	int k;
	int a;
	int s;
	int n;
	int i;
	int m;
	int numb;
printf("Введите номер алгоритма: ");
scanf("%d", &numb);
if (numb == 10){
	scanf("%d", &a);
	for (n=a, s=0; n!=0; n=n/10)
	      { k=n%10; s=s*10+k;}
	printf("a = %d, s = %d\n", a, s);
	}
	//Число задом наперёд
if (numb == 11) {
	scanf("%d", &n);
	for (k=0, m=1; m <= n; k++, m = m * 2);
	printf("k = %d\n", k-1); }
	//Между какими степенями двойки находится число
if (numb == 12) {
	scanf("%d", &a);
	for (n=a, s=0; n!=0; n=n/10)
      	{k=n%10; s=s+k;}
      	printf("a = %d s = %d\n", a, s);	}
	//Сумма цифр
if (numb == 13) {
	scanf("%d", &n);
	for (s=1, i=0; i<=n; i++)
	{s = s * 2;}
	printf("s = %d\n", s);
	}
	//Степень+1 двойки
if (numb == 14) {
	scanf("%d", &a);
	for (n=2; n<a; n++)
     	{if (a%n==0) break; }
	if (n==a) puts("Good");
	}
	//Число простое или нет
}
