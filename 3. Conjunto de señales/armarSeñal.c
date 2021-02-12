//Alondra Sánchez Molina
//Este programa arma una señal que imprime 10 numeros

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

void manejador(){		
	int n, df;
	df=open("datos.dat",0);
		
	for(int i=0; i<10; i++){
		read(df,&n,sizeof(int));
		printf("%d\n",n);
	}
}

int main(){
	pid_t pid;
	int n, df, status;
	
	struct sigaction S;
	
	pid = fork();
	
	if(pid>0){
		S.sa_handler=manejador;
		sigemptyset(&S.sa_mask);
		S.sa_flags=0;
		sigaction(SIGUSR1, &S, NULL);
		pause();
		if(WIFSIGNALED(status))
			printf("La señal que interrumpio es: %d\n", WTERMSIG(status));	
	}
	if(pid==0){
		df=creat("datos.dat", 0777);
		df=open("datos.dat",1);
		for(int i=0; i<10; i++)
			write(df,&i, sizeof(int));
		kill(getppid(), SIGUSR1);
	}
}
