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
	int idSeg, *ptr;
	int k=1, tam;
	int array[n];

	key_t key;
	key = ftok(".",'c'); 
	
	for(int i=0; i<n; i++){
		array[i]=2*k;
		k++;
	}
	
	tam = sizeof(array) *2;
	idSeg = shmget(key, tam, IPC_CREAT | 0777);
	printf("\nID de segmento: %d\n", idSeg);
	ptr = (int *)shmat(idSeg,0,0);
	
	for(int i=0; i<n; i++){
		*ptr=array[i];
		printf("%d\n",*ptr);
		*ptr++;
	}
	
}
