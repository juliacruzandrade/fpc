#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    const char* path;
} ThreadArgs;

void* do_sum(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    const char* path = args->path;

    sleep(1); // emulating an adittional delay of 1 second
	      //

    FILE *file = fopen(path, "rb");  // open in binary mode
    if (file == NULL) {

    }

    int sum = 0;
    int byte;

    while ((byte = fgetc(file)) != EOF) {
        sum += byte;
    }

    if (sum >= 0) {
        printf("%s : %d\n", path, sum);
    }

    fclose(file);
    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t threads[argc-1];
    ThreadArgs args[argc-1];
    for (int i = 1; i < argc; i++) {
        const char *path = argv[i];
        args[i].path = path;
        pthread_create(&threads[i], NULL, do_sum, &args[i]);
    }

    for (int i = 1; i < argc; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
