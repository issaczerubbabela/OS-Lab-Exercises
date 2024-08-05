#include<stdio.h>
#include<unistd.h>

int main()
{
	int a,b;
	int pipefd1[2], pipefd2[2];
	int o,p,q;
	int x=fork();
	if(x>0)
	{
		printf("Enter an integer: ");
		scanf("%i",a);
		write(pipefd1[1],a,sizeof(a));
	}
	else if(x==0)
	{
		int y = fork();
		if(y>0)
		{
			printf("Enter another integer: ");
			scanf("%i",b);
			write(pipefd2[1],b,sizeof(b));
			read(pipefd1[0],o,sizeof(o));
			write(pipefd2[1],o, sizeof(o));
		}
		else if(y==0)
		{
			read(pipefd1[0],p,sizeof(p));
			read(pipefd1[0],q,sizeof(q));
			printf("The sum of the two integers is: %d",p+q);
			
		}
		else printf("Failed");
		
	}
	else printf("Failed");
}
