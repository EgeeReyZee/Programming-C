#include <pthread.h>
#include <stdio.h>

void* thread_func(void* arg) {
    char** messages = (char**)arg;
    for (int i = 0; messages[i] != NULL; i++) {
        printf("%s\n", messages[i]);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    char* msgs[4][4] = {
        {"Поток 1 - строка 1", "Поток 1 - строка 2", "Поток 1 - строка 3", NULL},
        {"Поток 2 - строка 1", "Поток 2 - строка 2", "Поток 2 - строка 3", NULL},
        {"Поток 3 - строка 1", "Поток 3 - строка 2", "Поток 3 - строка 3", NULL},
        {"Поток 4 - строка 1", "Поток 4 - строка 2", "Поток 4 - строка 3", NULL},
    };

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, msgs[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
