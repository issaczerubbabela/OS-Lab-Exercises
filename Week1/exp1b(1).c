#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main()
{
	int pipefd[2];
	if(pipe(pipefd) < 0) printf("pipe failed\n");
	int x = fork();
	char str[] = "Hello my dear child";
	char inbuf[strlen(str)+1];
	if(x>0)
	{
		printf("Your mom has opened her mouth to utter something.\n");
		write(pipefd[1], str, strlen(str)+1);
	}
	else if(x==0)
	{
		printf("Harken ye simpleton\n");
		read(pipefd[0], inbuf, strlen(str)+1);
		printf("Your mom says: %s\n",inbuf);
	}
	else
	{
		printf("error occured\n");
	}
	return 0;
}
