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
    		sem_wait(readmutex);
    		while(*writecount>0);
    		*readcount+=1;
    		sem_post(readmutex);
    	}
    	if(*rw==2){
    		sem_wait(readmutex);
        	*readcount += 1;
        	if (*readcount == 1) {
            	sem_wait(writemutex);
        	}
        	sem_post(readmutex);
    	}
        printf("1. Read Content\n2. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) {
            char *s = shm;
            printf("SHM Content:\n");

            while (*s != '\0') {
                printf("%c", *s);
                s++;
            }
            printf("\n");

        } 
        else if (choice != 2) {
            printf("\nInvalid Choice!!!\n");
        }
        if(*rw==1){
    		sem_wait(readmutex);
    		*readcount-=1;
    		if(*readcount==0){
    			sem_post(writemutex);
    		}
    		sem_post(readmutex);
    	}
    	if(*rw==2){
    		sem_wait(readmutex);  
        	*readcount-= 1;
        	if(*readcount == 0){
            	sem_post(writemutex);
        	}
        	sem_post(readmutex);
    	}
    	

    } while (choice != 2);



    return 0;
}