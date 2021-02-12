//En este programa un proceso imprime su id; el proceso padre imprime su id y temporaliza a su hijo por 5 seg

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

pid_t pidM;

void manejador(){
	kill(pidM,SIGKILL);
}

int main(int argc, char *argv[]){

	struct sigaction r;
	int df, status;
	char num[10], salto;
	int n= atoi(argv[1]);
	salto='\n';
	pidM=fork(); 
		
	if(pidM>0){
		printf("El ID del padre es: %d\n",getpid());
		r.sa_handler=manejador;	
		sigemptyset(&r.sa_mask);
		r.sa_flags=0;
		
		sigaction(SIGALRM,&r,NULL);
		alarm(2);
		wait(&status);
	}
	else if(pidM==0){
		df=creat("datos.txt", 0777);
		df=open("datos.txt",1);
		for(int i=0;i<n;i++)
		{
			sprintf(num,"%i",getpid());
			num[strlen(num)+1]='\n';
			write(df,num,strlen(num));
			write(df,&salto,sizeof(salto));
		}
	}

}
