#include<stdio.h>

//process structure
struct process{
	// arrival time
	// burst time
	// finish time
	// status 1-over, 0-not over
	// turn around time = finish time - arrival time
	// waiting time = turn around time - burst time
	int at, bt, ft, status, tat, wt;
}p[10];

//no of processes
int n;

int dispatcher(int time){
	//dispatch process for current time
	//min_at to find the process with the earliest possible arrival time.
	int min_at = 9999;
	int index = -1;
	//check for unfinished process that has arrived before or on current time.
	//it should be less than min arrival time.
	for(int i=0;i<n;i++){
		if(p[i].status==0 && p[i].at<=time && p[i].at<min_at){
			min_at = p[i].at;
			index=i;
		}
	}
	return index;
}

int main(){
	//get number of processes from user
	printf("Enter the number of processes: ");
	scanf("%d",&n);

	//for each process get the arrival time and the burst time from the user.
	//set status for all processes to 0
	for(int i=0; i<n; i++){
		printf("enter the arrival time and the burst time of the process %d: \n",i+1);
		scanf("%d%d",&p[i].at,&p[i].bt);
		p[i].status=0;
	}

	//init current time, idle = 0
	int ct=0;
	int idle=0;
	int i=0; //iterator

	while(i<n){
		//dispatch next process for current time
		int index = dispatcher(ct);
		//if no process arriving at current time, consider it as idle, check process for next time stamp
		if(index==-1){
			ct++;
			idle++;
			continue;
		}
		//print out the idle time and set it back to 0 when process arrives
		if(idle>0);
		{
			printf("IDLE(%d-%d)",ct-idle,ct);
			idle=0;
		}
		//Print process for gantt chart: P1(when - when)
		//set ct to when the process finishes.
		//set ft, status, tat and wt and also increase i since a process got over.
		printf("P%d(%d-%d)",index+1,ct,ct+p[index].bt);
		ct+=p[index].bt;
		p[index].ft=ct;
		p[index].status=1;
		p[index].tat=ct-p[index].at; //finish time - arrival time
		p[index].wt=p[index].tat-p[index].bt;
		i++;
	}
	//print table
	printf("\nProcess\tAT\tBT\tFT\tTAT\tWT\n");
	//calculate total tat and wt to find the average tat and wt
	int s=0, w=0;
	for(int i=0; i<n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,p[i].at,p[i].bt,p[i].ft,p[i].tat,p[i].wt);
		s+=p[i].tat;
		w+=p[i].wt;
	}
	printf("Average TAT = %f , Average WT = %f",(float)s/n,(float)w/n);
}