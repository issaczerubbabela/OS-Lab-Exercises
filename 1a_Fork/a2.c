#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd1[2]; // Pipe between p1 and p2
    int fd2[2]; // Pipe between p2 and p3
    pid_t p1, p2, p3;
    int num1, num2, sum;

    // Create pipes
    pipe(fd1);
    pipe(fd2);

    p1 = fork();

    if (p1 == 0) {
        // Process p1
        close(fd1[0]); // Close read end
        printf("Enter an integer for p1: ");
        scanf("%d", &num1);
        write(fd1[1], &num1, sizeof(int));
        close(fd1[1]);
        exit(0);
    } else {
        p2 = fork();
        if (p2 == 0) {
            // Process p2
            close(fd1[1]); // Close write end from p1
            close(fd2[0]); // Close read end
            read(fd1[0], &num1, sizeof(int));
            printf("Enter an integer for p2: ");
            scanf("%d", &num2);
            write(fd2[1], &num1, sizeof(int));
            write(fd2[1], &num2, sizeof(int));
            close(fd1[0]);
            close(fd2[1]);
            exit(0);
        } else {
            // Process p3
            close(fd2[1]); // Close write end from p2
            read(fd2[0], &num1, sizeof(int));
            read(fd2[0], &num2, sizeof(int));
            sum = num1 + num2;
            printf("Sum of %d and %d (p3): %d\n", num1, num2, sum);
            close(fd2[0]);
            wait(NULL); // Wait for child processes to finish
        }
    }

    return 0;
}
