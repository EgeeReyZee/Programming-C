#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* thread_func(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Поток %ld: строка %d\n", pthread_self(), i + 1);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    sleep(2);

    for (int i = 0; i < 4; i++) {
        pthread_cancel(threads[i]);
        printf("Поток %ld был отменен\n", threads[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
