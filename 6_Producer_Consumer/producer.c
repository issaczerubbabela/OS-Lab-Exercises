#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>

int main() {
    key_t key1 = 1234;
    key_t key2 = 2345;
    key_t key3 = 3456;

    // Create shared memory for semaphore
    int shmid1 = shmget(key1, sizeof(sem_t), 0666 | IPC_CREAT);
    sem_t *mutex = (sem_t *) shmat(shmid1, NULL, 0);
    sem_init(mutex, 1, 1); // Initialize semaphore for mutual exclusion

    // Create shared memory for buffer
    int shmid2 = shmget(key2, 100, 0666 | IPC_CREAT);
    int *buffer = (int *) shmat(shmid2, NULL, 0);

    // Create shared memory for index
    int shmid3 = shmget(key3, sizeof(int), 0666 | IPC_CREAT);
    int *index = (int *) shmat(shmid3, NULL, 0);
    *index = 0; // Initialize index

    char input;
    while (1) {
        printf("Do you want to produce a value? (y/n): ");
        scanf(" %c", &input);

        if (input == 'n') {
            break;
        } else if (input == 'y') {
            sem_wait(mutex);
            printf("Enter value to be produced: ");
            scanf("%d", &buffer[*index]);
            printf("Produced %d\n", buffer[*index]);
            *index += 1;
            sem_post(mutex);
            sleep(3);
        }
    }

    // Detach from shared memory
    shmdt(mutex);
    shmdt(buffer);
    shmdt(index);

    return 0;
}