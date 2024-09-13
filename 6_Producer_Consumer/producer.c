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

    // mutex
    int shmid1 = shmget(key1, sizeof(sem_t), 0666 | IPC_CREAT);
    sem_t *mutex = (sem_t *) shmat(shmid1, NULL, 0);
    // I'm using sem_post and sem_wait instead of incrementing and decrementing mutex manually.
    sem_init(mutex, 1, 1);

    // buffer
    int shmid2 = shmget(key2, 100, 0666 | IPC_CREAT);
    int *buffer = (int *) shmat(shmid2, NULL, 0);

    // index
    int shmid3 = shmget(key3, sizeof(int), 0666 | IPC_CREAT);
    int *index = (int *) shmat(shmid3, NULL, 0);
    *index = 0;

    char input;
    while (1) {
        printf("Do you want to produce a value? (y/n): ");
        scanf(" %c", &input);

        if (input == 'n') {
            break;
        } else if (input == 'y') {
            if(*index==5){
                printf("Data Buffer Full\n");
                continue;
            }
            sem_wait(mutex);
            printf("Enter value to be produced: ");
            scanf("%d", &buffer[*index]);
            printf("Produced %d\n", buffer[*index]);
            *index += 1;
            sleep(3);
            sem_post(mutex);
        }
    }

    // Detach from shared memory
    shmdt(mutex);
    shmdt(buffer);
    shmdt(index);

    return 0;
}