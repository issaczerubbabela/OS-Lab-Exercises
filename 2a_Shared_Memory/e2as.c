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
    printf("Enter text (type 'end' on a new line to stop):\n");
    char *ptr = (char*)shared_memory;
    while (1) {
        fgets(buff, 100, stdin);
        buff[strcspn(buff, "\n")] = 0; // Remove newline character

        if (strcmp(buff, "end") == 0) {
            break;
        }

        strcpy(ptr, buff);
        ptr += strlen(buff);
        *ptr = '\n'; // Add newline character
        ptr++;
    }
    *ptr = '\0'; // Null-terminate the string

    printf("Data written to shared memory:\n%s\n", (char*)shared_memory);
    return 0;
}
