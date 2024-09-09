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

    // Attach to shared memory
    int shmid1 = shmget(key1, sizeof(sem_t), 0666);
    sem_t *mutex = (sem_t *) shmat(shmid1, NULL, 0);

    int shmid2 = shmget(key2, 100, 0666);
    int *buffer = (int *) shmat(shmid2, NULL, 0);

    int shmid3 = shmget(key3, sizeof(int), 0666);
    int *index = (int *) shmat(shmid3, NULL, 0);

    for (int i = 0; i < 5; i++) {
        sem_wait(mutex);
        if (*index > 0) {
            *index -= 1;
            printf("Consumed %d\n", buffer[*index]);
        } else {
            printf("Buffer is empty\n");
        }
        sem_post(mutex);
        sleep(3);
    }

    // Detach from shared memory
    shmdt(mutex);
    shmdt(buffer);
    shmdt(index);

    return 0;
}