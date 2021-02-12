//Alondra Sánchez Molina
//Este programa escribe numeros en dos archivos y procesos diferentes; despues, los suma en otro proceso con wait

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	pid_t pidQ, pidL;
	int df,dg,n1,n2,sum, status;
	
	pidQ=fork(); 
	if(pidQ>0){ //W
		pidL=fork();
		wait(&status);
		if(pidL>0){ //W
			wait(&status);
			df=open("datos1.dat",0);
			dg=open("datos2.dat",0);
			for(int i=0; i<10; i++){
				read(df,&n1,sizeof(int));
				read(dg,&n2,sizeof(int));
				sum=n1+n2;
				printf("La suma de %d mas %d es: %d\n",n1, n2, sum);
			}
		}	
		if(pidL==0){  //L
			df=creat("datos2.dat", 0777);
			df=open("datos2.dat",1);
			for(int i=1; i<24; i=i+2)
				write(df,&i,sizeof(int));
		}
	}
	if(pidQ==0){  //Q
		df=creat("datos1.dat", 0777);
		df=open("datos1.dat",1);
		for(int i=2; i<22; i=i+2)
			write(df,&i, sizeof(int));
	}
	return 0;
}
