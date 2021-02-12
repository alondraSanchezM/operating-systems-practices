//Alondra Sánchez Molina
//Este programa muestra la interaccion entre procesos padre, hijo y "nieto"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    pid_t pid, pid2;
    
    pid=fork();
    if(pid>0){
        printf("Soy el padre, Mi ID es: %d\n", getpid());
		printf("Soy el padre, El ID de mi padre es: %d\n", getppid());
		wait(NULL);
    }
	else if(pid==0){
		pid2=fork();
		if(pid2>0){
   	    	printf("La suma es: %d\n",7+2);
			printf("Soy el hijo, Mi ID es: %d\n", getpid());
			printf("Soy el hijo, El ID de mi padre es: %d\n", getppid()); 
			wait(NULL); 	
		}
		if(pid2==0){
			printf("La resta es: %d\n",7-2);
			printf("Soy el nieto, Mi ID es: %d\n", getpid());
			printf("Soy el nieto, El ID de mi padre es: %d\n", getppid());
		}
    }
}
