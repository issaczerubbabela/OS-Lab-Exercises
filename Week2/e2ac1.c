#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>

int main()
{
    int i;
    void *shared_memory;
    char buff[100];
    int shmid;

    // Get shared memory ID
    shmid = shmget((key_t)2345, 1024, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to shared memory
    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void*)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Print the data from shared memory
    printf("The Server sent : %s\n", (char*)shared_memory);

    // Detach from shared memory
    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    return 0;
}
