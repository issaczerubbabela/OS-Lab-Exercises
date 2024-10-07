#include<stdio.h>

int** calculateNeedMatrix(int* proc, int* need, int res, int n){

	//calculate the need matrix
	for(int i=0;i<n;i++){
		for(int j=0;j<res;j++){
			//need = max - allocated
			need[i][0][j] = proc[n][1][j]-proc[n][0][j];
		}
	}
	return need;
}
int*** giveSafeSequence(int* proc, int* available, int* need, int res, int n, int* safe){
	
	//checks for sequence with safe state else gives no safe state
	int safeSeq[n]; //done array to denote processes safely allocated
	for(int i=0;i<n;i++){
		safeSeq[i]=0;
	}

	int index=0;
	int neg=0;
	int sub;
	for(int i=0;i<n;i++){
		index++;
		if(safeSeq[i]>0){
			continue;
		}
		else{
			//for each process for each resource, subtract the available with the need and if no process satisfies(sequence array is empty)
			neg=0;
			for(int j=0;j<res;j++){
				sub = available[j] - need[i][0][j];
				if(sub<0){
					neg=1;
					break;
				}
			}
			if(neg==0){
				for(int j=0;j<res;j++){
					available[j] += proc[i][0][j];
					safeSeq[i]=index;
				}
			}
		}
		int nonzeroes=0;
		for(int x=0;x<n;x++){
			if(safeSeq[x]>0) nonzeroes++;
		}	
		if(nonzeroes!=index){
			print("Unsafe state detected");
			*safe = 0;
			break;
		}
	}
	*safe=1;
	return safeSeq;
}

int main(){
	int n;
	printf("Enter the number of processes: ");
	scanf("%d",&n);

	printf("Enter the number of resources: ");
	int res;
	scanf("%d",&res);

	int proc[n][2][res];
	int available[res];
	int need[n][1][res];

	for(int i=0;i<n;i++){
		printf("Enter the allocated resources for process %d: \n",i);
		for(int j=0;j<res;j++){
		printf("Resource %d:",j);
		scanf("%d",&proc[n][0][j]);
		}

		printf("Enter the maximum resources for process %d: \n",i);
		for(int j=0;j<res;j++){
		printf("\nResource %d:",j);
		scanf("%d",&proc[n][1][j]);
		}
	}
	
	//get available resources
	printf("Enter number of available resources: \n");
	for(int j=0;j<res;j++){
		printf("\nResource %d:",j);
		scanf("%d",&available[j]);
		}
	need = calculateNeedMatrix(proc, need, res, n);
	int safe=1;
	int* safeSeq = giveSafeSequence(proc[n][2][res], available[res], need[n][1][res], res, n, &safe);
	
	if(safe==1){
		printf("The safe sequence is:");
		for(int i=0;i<0;i++){
			if(safeSeq[i]==i+1){
				printf(" p%d",i);
			}
		}
	}
	return 0;
}
