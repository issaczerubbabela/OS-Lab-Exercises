#include<stdio.h>
struct process
{
	int at,bt1,bt2,io,ft,status,tat,wt,bt1done,arr;
}p[10];
int n;
int dispatcher(int time)
{
	int min_at = 9999,index=-1;
	for(int i=0;i<n;i++)
	{
		if(p[i].status == 0 && p[i].arr<=time && p[i].arr<min_at)
		{
			min_at = p[i].arr;
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
		scanf("%d%d%d%d",&p[i].at,&p[i].bt1,&p[i].io,&p[i].bt2);
		p[i].status =0;
        p[i].bt1done=0;
        p[i].arr=p[i].at;
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
        if(p[index].bt1done == 0)
        {
            p[index].bt1done=1;
            printf("P%d(%d-%d)",index+1,ct,ct+p[index].bt1);
            ct+=p[index].bt1;
            p[index].arr = ct+p[index].io;

        }
        else
        {
		printf("P%d(%d-%d)",index+1,ct,ct+p[index].bt2);
		ct+=p[index].bt2;
		p[index].ft=ct;
		p[index].status=1;
		p[index].tat=ct-p[index].at;
		p[index].wt=p[index].tat - p[index].bt1-p[index].bt2;
		i++;
        }
	}
	printf("\nProcess\tAT\tBT1\tIO\tBT2\tFT\tTAT\tWT\n");
	float s=0,w=0;
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,p[i].at,p[i].bt1,p[i].io,p[i].bt2,p[i].ft,p[i].tat,p[i].wt);
		s+=p[i].tat;
		w+=p[i].wt;
	}
	float wtt = w/n;
	float tatt = s/n;
	printf("Average TAT = %f , Average WT = %f",tatt,wtt);
}