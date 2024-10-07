#include<stdio.h>
struct process
{
	int at,bt,ft,status,tat,wt;
}p[10];
int n;
int dispatcher(int time)
{
	int min_bt = 9999,index=-1;
	for(int i=0;i<n;i++)
	{
		if(p[i].status == 0 && p[i].at<=time && p[i].bt<min_bt)
		{
			min_bt = p[i].bt;
			index=i;
		}
	}
	return index;
}
int main()
{
	printf("Enter number of processes: ");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("Enter AT and BT of process %d : ",i+1);
		scanf("%d%d",&p[i].at,&p[i].bt);
		p[i].status =0;
	}
	int i=0,ct=0,idle=0;
	while(i<n)
	{
		int index = dispatcher(ct);
		if(index==-1)
		{
			ct++;
			idle++;
			continue;
		}
		if(idle>0)
		{
			printf("IDLE(%d-%d)",ct-idle,ct);
			idle=0;
		}
		printf("P%d(%d-%d)",index,ct,ct+p[index].bt);
		ct+=p[index].bt;
		p[index].ft=ct;
		p[index].status=1;
		p[index].tat=ct-p[index].at;
		p[index].wt=p[index].tat - p[index].bt;
		i++;
	}
	printf("\nProcess\tAT\tBT\tFT\tTAT\tWT\n");
	float s=0,w=0;
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,p[i].at,p[i].bt,p[i].ft,p[i].tat,p[i].wt);
		s+=p[i].tat;
		w+=p[i].wt;
	}
	float wtt = w/n;
	float tatt = s/n;
	printf("Average TAT = %f , Average WT = %f",tatt,wtt);
}
