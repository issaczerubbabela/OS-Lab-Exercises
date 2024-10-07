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


void writeData() {
    system("gnome -terminal -- ./writer");
}


void readData() {
    system("gnome -terminal -- ./reader");
}


int main(){
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

    printf("1.Writer Priority \n2.Reader Priority\nEnter your Choice:");
    int rw_choice;
    scanf("%d",&rw_choice);
    getchar();
    *rw=rw_choice;

    sem_init(readmutex, 1, 0);
    sem_init(writemutex, 1, 0);
    sem_init(mutex, 1, 0);
    *readcount = 0;
    *writecount = 0;
    char pattern[10];
    printf("Enter the pattern");
    fgets(pattern,10,stdin);
    int n= strlen(pattern);
    if (pattern[n - 1] == '\n') {
        pattern[n - 1] = '\0';
    }
    n=strlen(pattern);
    int i=0;
    do{
        if(pattern[i]=='r'){
            readData();
        }
        else if(pattern[i]=='w'){
            writeData();
        }
        printf("Next Process?(press enter)");
        getchar();
        i=i+1;

    }while(i<n && pattern[i]!='\0');

    printf("Process Completed!!!");
    sem_wait(readmutex);
    sem_wait(writemutex);


    sem_destroy(readmutex);
    sem_destroy(writemutex);

    shmctl(shmid, IPC_RMID, NULL);
    shmctl(rwid, IPC_RMID, NULL);
    shmctl(readcountid, IPC_RMID, NULL);
    shmctl(writecountid, IPC_RMID, NULL);
    shmctl(readmutexid, IPC_RMID, NULL);
    shmctl(writemutexid, IPC_RMID, NULL);
}
