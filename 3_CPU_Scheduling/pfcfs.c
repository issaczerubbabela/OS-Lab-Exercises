#include <stdio.h>

struct process {
    int at;      // arrival time
    int st;      // service time
    int pr;      // priority
    int status;  // 1 - completed, 0 - not completed
    int ft;      // finish time
} ready_list[10];

int n;

// Function declaration for dispatcher
int dispatcher(int time);

int main() {
    int i, cur_time, pid;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("*\n");
        printf("Enter Arrival Time: ");
        scanf("%d", &ready_list[i].at);
        printf("Enter Service Time: ");
        scanf("%d", &ready_list[i].st);
        printf("Priority (1-10): ");
        scanf("%d", &ready_list[i].pr);
        ready_list[i].status = 0;
    }

    i = 0;
    cur_time = 0;

    while (i < n) { // until all the processes are completed
        pid = dispatcher(cur_time); // choose the next process for execution
        if (pid == -1) { // No process is ready at the current time
            cur_time++;   // Increment the current time and try again
            continue;
        }
        ready_list[pid].ft = cur_time + ready_list[pid].st; // update the finish time of the process
        ready_list[pid].status = 1; // Process completed
        cur_time = ready_list[pid].ft; // Update clock time to the finish time of the current process
        i++;
    }

    printf("Process\t Arrival Time\t Service Time\t Finish Time\n");
    printf("*\t ************\t ************\t ***********\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, ready_list[i].at, ready_list[i].st, ready_list[i].ft);
    }

    return 0;
}

// Function definition for dispatcher
int dispatcher(int time) {
    int i, high_pr = 9999, index = -1;
    for (i = 0; i < n; i++) {
        if (ready_list[i].status != 1) { // Process not completed
            if (ready_list[i].at <= time) { // Process’s arrival time is within the current time of the clock
                if (ready_list[i].pr < high_pr) {
                    high_pr = ready_list[i].pr;
                    index = i;
                }
            }
        }
    }
    return index;
}