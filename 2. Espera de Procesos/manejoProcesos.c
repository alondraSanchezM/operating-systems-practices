//Alondra Sánchez Molina
//Este programa escribe numeros en dos archivos y procesos diferentes; despues, los suma en otro proceso

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
	pid_t pidQ, pidL;
	int df,dg,n1,n2,sum, status;
	
	pidQ=fork(); 
	if(pidQ>0){ //W
		pidL=fork();
		if(pidL>0){ 
			wait(&status);
			df=open("datos1.dat",0);
			dg=open("datos2.dat",0);
			for(int i=0; i<20; i++){
				read(df,&n1,sizeof(int));
				read(dg,&n2,sizeof(int));
				sum=n1+n2;
				printf("La suma de %d mas %d es: %d\n",n1, n2, sum);
			}
		}	
		if(pidL==0){  //L
			wait(&status);
			df=creat("datos2.dat", 0777);
			df=open("datos2.dat",1);
			for(int i=1; i<48; i=i+2)
				write(df,&i,sizeof(int));
		}
	}
	if(pidQ==0){  //Q
		wait(&status);
		df=creat("datos1.dat", 0777);
		df=open("datos1.dat",1);
		for(int i=2; i<44; i=i+2)
			write(df,&i, sizeof(int));
	}
	return 0;
}
