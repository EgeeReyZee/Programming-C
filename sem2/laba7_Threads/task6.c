#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 50

int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
int n = sizeof(arr) / sizeof(arr[0]);

void* sleep_sort(void* arg) {
    int val = *(int*)arg;
    usleep(val * 1000000);
    printf("%d ", val);
    fflush(stdout);
    return NULL;
}

int main() {
    pthread_t threads[MAX];

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("\n");
    return 0;
}
