#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* do_sum(void* cpath) {

    const char *path = (const char *) cpath;

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
    for (int i = 1; i < argc; i++) {
        const char *path = argv[i];
        pthread_create(&threads[i-1], NULL, do_sum, &path);
    }

    for (int i = 1; i < argc; i++) {
        pthread_join(threads[i-1], NULL);
    }

    return 0;
}
