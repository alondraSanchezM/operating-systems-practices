//Alondra Sánchez Molina
//Este programa muestra el uso de pidet fork()

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	pid_t pid;
	int n, status, df;
	
	
	pid = fork();
	
	if(pid>0){
		wait(&status);
		df=open("datos.dat",0);
		for(int i=0; i<10; i++){
			read(df,&n,sizeof(int));
			printf("%d\n",n);
		}
	}
	if(pid==0){
		df=creat("datos.dat", 0777);
		df=open("datos.dat",1);
		for(int i=0; i<10; i++)
			write(df,&i, sizeof(int));
	}
}
