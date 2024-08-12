
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd1[2];
    char string[] = "Hello Child ";
    char inbuf[strlen(string) + 5];
    
        
    if (pipe(fd1)<0) printf("pipe failed\n");
    
    int x = fork();
    if (x == 0)
    {
        close(fd1[1]); // Close the write end in the child process
        printf("This is a child process: %d and its parent is: %d\n", getpid(), getppid());
        read(fd1[0], inbuf, strlen(string) + 5);
        printf("Your parent says: %s\n", inbuf);
        close(fd1[0]); // Close the read end in the child process
        exit(0);
    }
    else if (x > 0)
    {
        close(fd1[0]); // Close the read end in the parent process
        char new[4];
        sprintf(new, "%d", getpid());
        char message[strlen(string) + strlen(new) + 1];
        strcpy(message, string);
        strcat(message, new);
        write(fd1[1], message, strlen(message) + 1);
        printf("The parent has spoken, ye foolish child\n");
        close(fd1[1]); // Close the write end in the parent process
        wait(NULL); // Wait for the child process to finish
    }
    else
    {
        printf("Error encountered\n");
    }

    return 0;
}

