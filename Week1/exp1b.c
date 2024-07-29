	#include <string.h>
	#include <stdio.h>
	#include <sys/wait.h>
	#include <unistd.h>
	#include <stdlib.h>

	int main()
	{
		int fd1[2];	
		char string[] = "Hello Child";
		char inbuf[strlen(string)+5];
		int i;
		if(pipe(fd1) < 0) printf("pipe failed\n");
		int x = fork();
		if(x>0)
		{
			char new[4];
			int pid = getpid();
			sprintf(new, '%d', pid);
			write(fd1[1],strcat(string,new),strlen(string)+5);
			printf("the parent %s has spoke ye foolish child\n",getpid());
		}
		else if(x==0)
		{
			printf("This is a child process : %d and its parent is : %d\n",getpid(),getppid());
			read(fd1[0],inbuf,strlen(string)+5);
			printf("Your parent says : %s\n",inbuf);
		
		}
		else
		{
			printf("error encountered");
		}
	
	}
