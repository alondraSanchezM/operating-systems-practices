#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]){

	int n=atoi(argv[1]); 
	int idSeg, *a;
	int k=1, tam;
	int arr[n];

	key_t clave;
	clave = ftok(".",'I'); 
	
	for(int i=0; i<n; i++){
		arr[i]=3*k;
		k=k+2;
	}
	
	tam = sizeof(arr);
	idSeg = shmget(clave, tam , IPC_CREAT | 0777);
	printf("\nID de segmento: %d\n", idSeg);
	a = (int *)shmat(idSeg,0,0);
	
	

	for(int i=0; i<n; i++){
		*a=arr[i];
		printf("%d\n",*a);
		*a++;
	}
	
}
