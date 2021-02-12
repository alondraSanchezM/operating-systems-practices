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
	int idSegS, idSegP, idSegI, *aS, *aP, *aI;
	int tam, sum;
	int arrS[n], arrP[n], arrI[n];

	key_t claveI, claveP, claveS;
	claveS = ftok(".",'K');
	claveP = ftok(".",'P');  
	claveI = ftok(".",'I'); 
	 
	idSegS = shmget(claveS, sizeof(arrS), IPC_CREAT | 0777);
	idSegP = shmget(claveP, sizeof(arrP), IPC_CREAT | 0777);
	idSegI = shmget(claveI, sizeof(arrI), IPC_CREAT | 0777);
	
	printf("\nIDs de segmentos; par: %d, ID impar: %d, ID suma: %d \n", idSegP, idSegI, idSegS);
	aS = (int *)shmat(idSegS,0,0);	
	aI = (int *)shmat(idSegI,0,0);
	aP = (int *)shmat(idSegP,0,0);
		
	for(int i=0; i<n; i++){
		arrP[i] = *aP;
		arrI[i] = *aI;
		*aS=arrP[i] + arrI[i];
		*aS++;
		*aP++;
		*aI++;
	}	
		
	for(int i=0;i<n;i++)
		*aS--;
		
	for(int i=0; i<n; i++){	
		arrS[i] = *aS;
		printf("La suma de %d mas %d es: %d\n",arrP[i], arrI[i], arrS[i]);
		*aS++;	
	}
	
	shmdt(aS);
	shmctl(idSegS,IPC_RMID,NULL);
	
	shmdt(aP);
	shmctl(idSegP,IPC_RMID,NULL);
	
	shmdt(aI);
	shmctl(idSegI,IPC_RMID,NULL);
	
}
