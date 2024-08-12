#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include<ctype.h> // Include ctype.h for toupper function

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

    // Read the string from shared memory
    strcpy(buff, (char*)shared_memory);

    // Convert the string to uppercase
    char newString[100];
    int j = 0;
    while (buff[j] != '\0') {
        newString[j] = toupper(buff[j]);
        j++;
    }
    newString[j] = '\0';

    // Save the string to a file
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("fopen failed");
        exit(1);
    }
    fprintf(file, "%s", newString);
    fclose(file);

    // Use the wc command to find the number of lines, words, and characters
    system("wc output.txt");

    // Detach from shared memory
    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    return 0;
}
