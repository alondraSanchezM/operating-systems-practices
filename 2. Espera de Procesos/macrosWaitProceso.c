//Alondra Sánchez Molina
//Manejo de macros y wait en S.O.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	pid_t pid;
	int IDhijo, status;
	
	pid = fork();
	
	if(pid>0){
		IDhijo = wait(&status);
		if(WIFEXITED(status))
			printf("Estado del hijo %d\n", WEXITSTATUS(status));
		printf("ID del proceso %d\n", getpid());
		printf("ID del proceso hijo %d\n", IDhijo);
	}
	else if(pid==0){
		printf("ID del padre %d\n", getppid());
		return (10);
	}
}
