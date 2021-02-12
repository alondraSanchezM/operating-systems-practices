//Alondra Sánchez Molina
//Este programa escribe numeros en dos archivos y usa señales

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

void manejador(){
	int df,dg,n1,n2;
	
	df=open("datos1.dat",0);
	dg=open("datos2.dat",0);
			
	for(int i=0; i<20; i++){
		read(df,&n1,sizeof(int));
		read(dg,&n2,sizeof(int));
		printf("La suma de %d mas %d es: %d\n",n1, n2, n1+n2);
	}
}

int main(){
	pid_t pidQ, pidL;
	int df,dg,n1,n2,sum, status;
	struct sigaction p;
	struct sigaction i;
	
	pidQ=fork(); 
	if(pidQ>0){ //W
		pidL=fork();
		if(pidL>0){ 
			p.sa_handler=manejador;	
			sigemptyset(&p.sa_mask);
			p.sa_flags=0;
			
			i.sa_handler=manejador;	
			sigemptyset(&i.sa_mask);
			i.sa_flags=0;
			
			sigaction(SIGUSR1, &p, NULL);
			sigaction(SIGUSR2, &i, NULL);
			pause();
		}	
		if(pidL==0){  //L
			df=creat("datos2.dat", 0777);
			df=open("datos2.dat",1);
			for(int i=1; i<48; i=i+2)
				write(df,&i,sizeof(int));
			kill(getppid(),SIGUSR1);
		}
	}
	if(pidQ==0){  //Q
		df=creat("datos1.dat", 0777);
		df=open("datos1.dat",1);
		for(int i=2; i<44; i=i+2)
			write(df,&i, sizeof(int));
		kill(getppid(),SIGUSR2);
	}
	return 0;
}
