#include<stdio.h>

int* calculateNeedMatrix(int* proc, int* need, int res, int n){

	//calculate the need matrix
	for(int i=0;i<n;i++){
		for(int j=0;j<res;j++){
			//need = max - allocated
			need[i][0][j] = proc[n][1][j]-proc[n][1][j]
		}
	}
	return need;
}
int* giveSafeSequence(int* proc, int* available, int* need, int res, int n, int* safe){
	
	//checks for sequence with safe state else gives no safe state
	int done[n]; //done array to denote processes safely allocated
	for(int i=0;i<n;i++{
		done[i]=0;
	}

	for(int i=0;i<n;i++){
		if(done[i]==1){
			continue 
		}
		else{
			
		}
	}
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
	
}
