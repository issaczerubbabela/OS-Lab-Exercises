#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int i;
	for(i=0;i<2;i++)
	{	
		int x = fork();
		if(x==0)
		{
			printf("This is a child process : %d and its parent is : %d\n",getpid(),getppid());
			
		}
		else if (x<0)
		{
			printf("error encountered");
		}
	}
	wait(NULL);
	printf("This is a parent process: %d\n",getpid());
	
}
