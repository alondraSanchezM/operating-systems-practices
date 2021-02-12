//Este programa muestra el manejo de señales de usuario

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

pid_t pidA, pidB, pidC;

void manejadorR(){
	kill(pidA,SIGKILL);
	kill(pidB,SIGKILL);
	kill(pidC,SIGKILL);
}

void manejadorA(){
 	kill(pidA,SIGUSR1);
}
 
void manejadorB(){
  	kill(pidB,SIGUSR2);
} 

void manejadorC(){
 	kill(pidC,SIGUSR1);
}
 

int main(){
	char idb[10], idc[10];
	int db, dc;
	struct sigaction act;
	pidA=fork();
	
	if(pidA>0){//Padre  R
		act.sa_handler=manejadorR;	
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;
		sigaction(SIGUSR1, &act, NULL);
		pause();		
	}else if(pidA==0){//A
		pidB=fork();
		if(pidB>0){//A
			act.sa_handler=manejadorA;	
			sigemptyset(&act.sa_mask);
			act.sa_flags=0;
			sigaction(SIGUSR2, &act, NULL);
			
			for(;;){
				printf("Soy A, el ID de mi padre es:%d\n", getppid());		
			}
		}else if(pidB==0){//B
			pidC=fork();			
			if(pidC>0){//B
				db=creat("idB.txt", 0777);
				db=open("idB.txt",1);
				sprintf(idb,"%i",getpid());				
				write(db,idb,strlen(idb));

				act.sa_handler=manejadorB;	
				sigemptyset(&act.sa_mask);
				act.sa_flags=0;
				sigaction(SIGUSR1, &act, NULL);
				
				for(;;){
					printf("Soy B, el ID de mi padre es:%d\n", getppid());		
				}
			}else if(pidC==0){//C	
				dc=creat("idC.txt", 0777);
				dc=open("idC.txt",1);
				sprintf(idc,"%i",getpid());				
				write(dc,idc,strlen(idc));

				act.sa_handler=manejadorC;	
				sigemptyset(&act.sa_mask);
				act.sa_flags=0;				
				sigaction(SIGALRM,&act,NULL);
				alarm(6);

				for(;;){
					printf("Soy C, el ID de mi padre es:%d\n", getppid());		
				}
			}
		}
	}
}

