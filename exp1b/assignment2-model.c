#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int a, b;
    int pipefd1[2], pipefd2[2];
    int o, p, q;
    pipe(pipefd1);
    pipe(pipefd2);

    pid_t x = fork();
    if (x > 0)
    {
        // Parent process (Process 1)
        printf("Enter an integer: ");
        scanf("%d", &a);
        write(pipefd1[1], &a, sizeof(a));
        close(pipefd1[1]); // Close write end of pipe1
        wait(NULL); // Wait for child process 2 to finish
    }
    else if (x == 0)
    {
        pid_t y = fork();
        if (y > 0)
        {
            // First child process (Process 2)
            read(pipefd1[0], &o, sizeof(o));
            printf("Enter another integer: ");
            scanf("%d", &b);
            write(pipefd2[1], &b, sizeof(b));
            close(pipefd1[0]); // Close read end of pipe1
            close(pipefd2[1]); // Close write end of pipe2
        }
        else if (y == 0)
        {
            // Second child process (Process 3)
            read(pipefd2[0], &p, sizeof(p));
            read(pipefd2[0], &q, sizeof(q));
            printf("The sum of the two integers is: %d\n", p + q);
        }
        else
        {
            perror("Failed to fork");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        perror("Failed to fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}
