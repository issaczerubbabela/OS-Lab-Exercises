
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	int bd[2];
	char a[] = "hi	";
	char inbuf[strlen(a)+1];
	char b[] = "bye";
	char outbuf[strlen(a) + strlen(b) + 1];
	char c[strlen(a) + strlen(b) + 1];
	pid_t p;
		
	if(pipe(fd)<0) 
	{
		perror("forward pipe failed");
		exit(1);
	}
	if(pipe(bd)<0)
	{
		perror("backward pipe failed");
		exit(1);
	}
	
	p = fork();
	
	if(p>0)
	{
		write(fd[1], a, strlen(a)+1);
		read(bd[0], outbuf, strlen(a)+strlen(b)+1);
		printf("the concatenated string is: %s\n",outbuf);
		
	}
	else if(p==0)
	{
		read(fd[0], inbuf, strlen(a)+1);
		strcpy(c, inbuf);
		strcat(c,b);
		write(bd[1], c, strlen(c)+1);
	}
	return 0;
}

