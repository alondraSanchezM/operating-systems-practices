//Mecanismos de comunciación. Memoria Compartida y Cola de Mensajes

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

struct data{
	float x;
	int y;
	char cad[20];
};

int main(int argc, char **argv){
	
	int n, i, idShmC, idShmD, idQueue;
	int fdFifo;
	
	key_t keyCshm, keyDshm, keyQueue;
	pid_t pidD, pidE;
	
	n=atoi(argv[1]);
	struct data nStruct[n], *apC;

	struct mymsgbuf{
				long type;
				struct data nStructQ[n];
	}mybuf;	
	
	pidD=fork();
	if(pidD>0){ //C
		char *mififo = "/home/alondra/Escritorio/Programas S.O. I/15. Medios de comunicación entre procesos/mififo"; 
		mkfifo(mififo, 0666); 
		
		fdFifo = open(mififo, O_RDONLY); 
		read(fdFifo,&nStruct,sizeof(nStruct));
		/*for(i=0;i<n;i++){
			printf("\nFIFOS datos de la estructura no.%d son:\n", i+1);
			printf("%.2f\n",nStruct[i].x);	
			printf("%d\n",nStruct[i].y);	
			printf("%s\n",nStruct[i].cad);	
		}*/
		keyCshm = ftok(".",'s');
  		idShmC = shmget(keyCshm,sizeof(nStruct),IPC_CREAT | 0777);
  		apC = (struct data *)shmat(idShmC,0,0);
  
  		for(int i=0; i<n; i++){
  			*apC = nStruct[i];
  			*apC++;
  		}
  		//printf("\nZona de Memoria creada con ID: %d", idShmC);
	}else if(pidD==0){ //D
		pidE=fork();
		if(pidE>0){
			struct data nStructAux[n], *apD;
			
			keyDshm = ftok(".",'s');
    		idShmD=shmget(keyDshm,sizeof(nStructAux),0);
    		//printf("\nZona de memoria reconocida ID: %d", idShmD);
    		apD = (struct data*)shmat(idShmD,0,0);
    		
    		for(int i=0; i<n; i++){
  				nStructAux[i] = *apD;
  				*apD++;
  			}
    		for(i=0;i<n;i++){
				printf("\nSHM datos de la estructura no.%d son:\n", i+1);
				printf("%.2f\n",nStructAux[i].x);	
				printf("%d\n",nStructAux[i].y);	
				printf("%s\n",nStructAux[i].cad);	
			}
    		shmdt(apD);
    		shmctl(idShmD,IPC_RMID,NULL);
    		//printf("Zona de memoria liberada.\n");
    		
			
			keyQueue=ftok(".",'Q');
			idQueue=msgget(keyQueue, 0600 | IPC_CREAT);
			
			mybuf.type= 1;
			for(int i=0; i<n; i++)
				mybuf.nStructQ[i] = nStructAux[i];
				
			msgsnd(idQueue, (struct msgbuf *)&mybuf, sizeof(struct mymsgbuf),IPC_NOWAIT);
    		
    	}else if(pidE==0){ //E
  		
			keyQueue=ftok(".",'Q');
			idQueue=msgget(keyQueue, 0600 | IPC_CREAT);
    		msgrcv(idQueue, (struct msgbuf *)&mybuf, sizeof(mybuf.type)+sizeof(mybuf.nStructQ),1,0);
    		for(i=0;i<n;i++){
				printf("\nQueue datos de la estructura no.%d son:\n", i+1);
				printf("%.2f\n",mybuf.nStructQ[i].x);	
				printf("%d\n",mybuf.nStructQ[i].y);	
				printf("%s\n",mybuf.nStructQ[i].cad);	
			}
    		wait(NULL);
    	}
	}
	msgctl(idQueue, IPC_RMID, 0);
}

