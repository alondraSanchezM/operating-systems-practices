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
	int k=1, tam, sum;
	int array[n];
	int j=n;
	n=n*2;

	key_t key;
	key = ftok(".",'c'); 
	
	tam = sizeof(array) *2;
	idSeg = shmget(key, tam, 0);
	printf("\nD de segmento: %d\n", idSeg);
	ptr = (int *)shmat(idSeg,0,0);
	
	for(int i=0; i<n; i++){
		array[i] = *ptr;
		printf("%d\n",array[i]);
		*ptr++;
	}	
	
	for(int i=0; i<n/2; i++){
		printf("La suma de %d mas %d es: %d\n",array[i], array[j], array[i]+array[j]);
		j++;
	}
	
	shmdt(ptr);	
	shmctl(idSeg,IPC_RMID,NULL);
	
}
