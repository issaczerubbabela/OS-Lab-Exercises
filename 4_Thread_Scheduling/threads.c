#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Define the thread data structure
typedef struct {
    int *array;
    int start;
    int end;
    int search;
    int *count;
    pthread_mutex_t *mutex;  // Mutex to synchronize count updates
} ThreadData;

// Thread function to search for occurrences of 'search' in a segment of the array
void* search_scores(void* arg) {
    ThreadData data = (ThreadData) arg;
    int local_count = 0;

    for (int i = data->start; i < data->end; i++) {
        if (data->array[i] == data->search) {
            local_count++;
        }
    }

    // Lock the mutex before updating the shared count
    pthread_mutex_lock(data->mutex);
    *(data->count) += local_count;
    pthread_mutex_unlock(data->mutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <file> <S> <threads> <segment_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    int search_value = atoi(argv[2]);
    int num_threads = atoi(argv[3]);
    int segment_size = atoi(argv[4]);

    // Open the file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // Read scores into an array
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    int num_scores = file_size / sizeof(int);
    int *scores = malloc(file_size);
    fread(scores, sizeof(int), num_scores, file);
    fclose(file);

    // Create threads and perform search
    pthread_t threads[num_threads];
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    int count = 0;

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        ThreadData *data = malloc(sizeof(ThreadData));
        data->array = scores;
        data->start = i * segment_size;
        data->end = (i + 1) * segment_size;
        if (data->end > num_scores) data->end = num_scores; // Handle last segment
        data->search = search_value;
        data->count = &count;
        data->mutex = &mutex;

        pthread_create(&threads[i], NULL, search_scores, data);
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result
    printf("Number of students who scored %d: %d\n", search_value, count);

    // Clean up
    pthread_mutex_destroy(&mutex);
    free(scores);

    return EXIT_SUCCESS;
}