#include<stdio.h>
#include<math.h>

struct process{
	int at,bt,ct,tat,wt,arr,rt,done;  // 1-completed, 0-not completed
}processes[10];

int dispatcher(int time, int n){
	int min = 9999;
	int ind = -1;
	for(int i=0; i<n; i++){
		if((processes[i].done==0) && (processes[i].arr<=time) && (processes[i].arr<=min) && (processes[i].rt>0)){
			min = processes[i].arr;
			ind = i;
		}
	}
	return ind;
}

int main(){
	int n;
	printf("Enter no. of processes: ");
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		printf("Process %d\n", i+1);
		printf("Enter Arrival time: ");
		scanf("%d", &processes[i].at);
		printf("Enter Burst time: ");
		scanf("%d", &processes[i].bt);
		processes[i].rt = processes[i].bt;
		processes[i].arr = processes[i].at;
		processes[i].done=0;
	}
	int quant;
	printf("Enter RR time quantum: ");
	scanf("%d", &quant);
	int done = 0,curr_time = 0,pid,idle=0;
	while(done<n){
		pid = dispatcher(curr_time, n);
		if(pid!=-1){
		    if(idle>0)
		    {
		        printf("IDLE(%d-%d)",curr_time-idle,curr_time);
		        idle=0;
		    }
			if (processes[pid].done!=1){
				if (processes[pid].rt>quant){
				    printf("P%d(%d-%d)",pid,curr_time,curr_time+quant);
					processes[pid].rt-=quant;
					curr_time += quant;
					processes[pid].arr = curr_time;
				}
				else{
				    printf("P%d(%d-%d)",pid,curr_time,curr_time+processes[pid].rt);
					if (processes[pid].rt==quant){
						curr_time+=quant;
					}
					else{
						curr_time+=processes[pid].rt;
					}
					processes[pid].rt = 0;
					processes[pid].done = 1;
					done++;
					processes[pid].ct = curr_time;
					processes[pid].tat = processes[pid].ct - processes[pid].at;
					processes[pid].wt = processes[pid].tat - processes[pid].bt;
				}
		
			}
		}
		else{
		    idle++;
			curr_time++;
		}			
	}
	printf("\nProcess\t Arrival Time\t Burst Time\t Completion Time\t TA Time\t Waiting Time\n");
	for(int i=0; i<n;i++){
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
	}
	float mean_tat = 0;
	float mean_wt = 0;
	for(int i=0; i<n; i++){
		mean_tat+=processes[i].tat;
		mean_wt+=processes[i].wt;
	}
	mean_tat/=n;
	mean_wt/=n;
	printf("Mean TA Time: %f\n", mean_tat);
	printf("Mean Waiting Time: %f\n", mean_wt); 
}

/*
Enter no. of processes: 5
Process 1
Enter Arrival time: 1 
Enter Burst time: 4
Process 2
Enter Arrival time: 0
Enter Burst time: 6
Process 3
Enter Arrival time: 2
Enter Burst time: 2
Process 4
Enter Arrival time: 4
Enter Burst time: 5
Process 5
Enter Arrival time: 3
Enter Burst time: 7
Enter RR time quantum: 2
Process	 Arrival Time	 Burst Time	 Completion Time	 TA Time	 Waiting Time
0		1		4		14		13		9
1		0		6		16		16		10
2		2		2		6		4		2
3		4		5		23		19		14
4		3		7		24		21		14
Mean TA Time: 14.600000
Mean Waiting Time: 9.800000
*/