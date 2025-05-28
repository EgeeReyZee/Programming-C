#include <pthread.h>
#include <stdio.h>

void* thread_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Дочерний поток: строка %d\n", i + 1);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);

    for (int i = 0; i < 5; i++) {
        printf("Родительский поток: строка %d\n", i + 1);
    }

    pthread_join(thread, NULL);
    return 0;
}
