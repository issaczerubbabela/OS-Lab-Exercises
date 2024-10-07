#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <semaphore.h>

#define SHMSZ 1024

int main() {
    int shmid,rwid,readcountid,writecountid,readmutexid,writemutexid,mutexid;
    key_t key = 1234;
    key_t key2=2345;
    key_t key3=4567;
    key_t key4=5678;
    key_t key5=6789;
    key_t key6=7890;
    key_t key7=8901;

    if ((shmid = shmget(key, SHMSZ, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    if ((rwid = shmget(key2, SHMSZ, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    if ((readcountid = shmget(key3, SHMSZ, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    if ((writecountid = shmget(key4, SHMSZ, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    if ((writemutexid = shmget(key5, SHMSZ, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    if ((readmutexid = shmget(key6, SHMSZ, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    if ((mutexid = shmget(key7, SHMSZ, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    char *shm;
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    int *rw,*readcount,*writecount;
    sem_t *writemutex,*readmutex,*mutex;
    if ((rw = shmat(rwid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    if ((readcount = shmat(readcountid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    if ((writecount = shmat(writecountid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    if ((readmutex = shmat(readmutexid, NULL, 0)) == (sem_t *) -1) {
        perror("shmat");
        exit(1);
    }
    if ((writemutex = shmat(writemutexid, NULL, 0)) == (sem_t *) -1) {
        perror("shmat");
        exit(1);
    }
    if ((mutex = shmat(mutexid, NULL, 0)) == (sem_t *) -1) {
        perror("shmat");
        exit(1);
    }

    int choice;
    do {
    	if(*rw==1){
    		sem_wait(writemutex);
    		*writecount+=1;
    		while(*readcount>0);
    	}
    	if(*rw==2){
    		sem_wait(writemutex);

    	}
        printf("1. Append Content\n2. Erase Content\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) {
            sem_wait(mutex);
            char *s = shm;
            int i = 0;
            printf("SHM Content:\n");

            while (*s != '\0') {
                printf("%c", *s);
                s++;
                i++;
            }
            printf("\n");

            int size = SHMSZ - i - 1;
            if (size <= 0) {
                printf("SHM full!!!\n");
            } else {
                char str[size + 1];
                printf("Enter content to append:");
                fgets(str, size + 1, stdin); 

                s = shm + i; 
                strncpy(s, str, size); 
                s[i + strlen(str)] = '\0'; 

                // Print updated content
                printf("After Writing SHM Content:\n");
                s = shm;
                while (*s != '\0') {
                    printf("%c", *s);
                    s++;
                }
                printf("\n");
            }
            sem_post(mutex);
        } else if (choice == 2) {
            char *s = shm;
            printf("SHM Content before erasing:\n");
            while (*s != '\0') {
                printf("%c", *s);
                *s = '\0';
                s++;
            }
            printf("\nContent Cleared!!!\n");
        } else if (choice != 3) {
            printf("\nInvalid Choice!!!\n");
        }
        if(*rw==1){
    		*writecount-=1;
    		sem_post(writemutex);
    	}
    	if(*rw==2){
    		sem_post(writemutex);

    	}

    } while (choice != 3);



    return 0;
}