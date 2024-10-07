#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int a,b;
	int pipefd1[2], pipefd2[2];
	pipe(pipefd1);
	pipe(pipefd2);

	pid_t p1=fork();
	if(p1==0)
	{
		close(pipefd1[0]);
		printf("Enter an integer: ");
		scanf("%i",&a);
		write(pipefd1[1],&a,sizeof(int));
		close(pipefd1[1]);
		exit(0);
	}
	else
	{
		pid_t p2 = fork();
		if(p2==0)
		{
			close(pipefd1[1]); // Close write end from p1
            		close(pipefd2[0]); // Close read end
			read(pipefd1[0],&a,sizeof(int));
			printf("Enter another integer: ");
			scanf("%i",&b);
			write(pipefd2[1],&a,sizeof(int));
			write(pipefd2[1],&b, sizeof(int));
			close(pipefd1[0]);            
			close(pipefd2[1]);
			exit(0);
		}
		else
		{
			close(pipefd2[1]);
			read(pipefd1[0],&a,sizeof(int));
			read(pipefd1[0],&b,sizeof(int));
			printf("The sum of the two integers is: %d",a+b);
			close(pipefd2[0]);
            		wait(NULL); // Wait for child processes to finish
		}
	}
}
