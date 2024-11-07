#include<stdio.h>
#include<stdlib.h>

#define frames 3
int main(){
	int incomingStream[]={1,2,3,4,2,1,5,3};
	int pageFaults = 0;
	int s;
	int pages = sizeof(incomingStream)/sizeof(int);
	printf("Incoming \t\t Frame 1 \t\t Frame 2 \t\t Frame 3 ");
	int temp [frames];
	for(int m=0; m<frames; m++){
		temp[m] = -1;
	}
	for(int m=0; m<pages; m++){
		s=0;
		for(int n=0; n<frames; n++){
			if(incomingStream[m] == temp[n]){
				s++;
				pageFaults--;
			}
		}
		pageFaults++;
		if((pageFaults <= frames) && (s==0)){
			temp[m] = incomingStream[m];
		} else if(s==0){
			temp[(pageFaults - 1)%frames] = incomingStream[m];
		}
		printf("\n");
		printf("%d\t\t\t",incomingStream[m]);
        for(int n = 0; n < frames; n++){
            if(temp[n] != -1) printf(" %d\t\t\t", temp[n]);
            else printf(" - \t\t\t");
        }
			
	}
	printf("\nTotal Page Faults:\t%d\n", pageFaults);
    return 0;
}
