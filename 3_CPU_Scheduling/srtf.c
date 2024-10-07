#include<stdio.h>
struct process
{
	int at,bt,ft,status,tat,wt,rt;
}p[10];
int n;
int dispatcher(int time)
{
	int min_rt = 9999,index=-1;
	for(int i=0;i<n;i++)
	{
		if(p[i].status == 0 && p[i].at<=time && p[i].rt<min_rt)
		{
			min_rt = p[i].rt;
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
		p[i].rt = p[i].bt;
	}
	int i=0,ct=0,idle=0;
	printf("Enter TIme Quantum: ");
	int tq;
	scanf("%d",&tq);
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
		if(p[index].rt>tq)
		{
			printf("P%d(%d-%d)",index+1,ct,ct+tq);
			p[index].rt-=tq;
			ct+=tq;
		}
		else
		{
			printf("P%d(%d-%d)",index+1,ct,ct+p[index].rt);
			ct+=p[index].rt;
			p[index].ft=ct;
			p[index].status=1;
			p[index].tat=ct-p[index].at;
			p[index].wt=p[index].tat - p[index].bt;
			i++;
		}
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