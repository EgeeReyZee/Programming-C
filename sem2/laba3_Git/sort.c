#include <stdio.h>

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int BubbleSort(int arr[], int n) {
    int Cf = 0;
    int Mf = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            Cf += 1;
            if (arr[j] < arr[j - 1]) {
                swap(&arr[j], &arr[j - 1]);
                Mf += 3;
            }
        }
    }
    return Mf+Cf;
}
//619 will do that
//I'll do that

void main() {
	int a[] = {2, 0};
	BubbleSort(a, 2);	
}
