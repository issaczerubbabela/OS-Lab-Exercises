#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct my_msg{
	long int msg_type;
	char some_text[BUFSIZ];
};

int main()
{
	int running = 1;
	int msgid;
	int rollno;
	struct my_msg some_data;
	long int msg_to_rec=0;
	msgid = msgget((key_t)12345,0666|IPC_CREAT);
	while(running)
	{
		printf("enter the customer number: ");
		msgrcv(msgid,(void*)&some_data,BUFSIZ,msg_to_rec,0);
		if(some_data.msg_type == rollno)
		printf("Amount to be paid: %s\n",some_data.some_text);
		if(strncmp(some_data.some_text,"end",2)==0) running=0;
	}
	msgctl(msgid,IPC_RMID,0);
}
