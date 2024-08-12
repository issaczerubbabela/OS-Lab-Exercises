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
    shmid = shmget((key_t)2345, 1024, 0666);
    printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    printf("Process attached at %p\n", shared_memory);

    // Loop to read input until "end" is encountered
    while (1) {
        printf("Enter some text (type 'end' to stop): ");
        fgets(buff, 100, stdin);
        buff[strcspn(buff, "\n")] = 0; // Remove newline character

        if (strcmp(buff, "end") == 0) {
            break;
        }

        strcpy((char*)shared_memory, buff);
        printf("Data written to shared memory: %s\n", (char*)shared_memory);
    }

    printf("Data read from shared memory is: %s\n", (char*)shared_memory);
    return 0;
}
