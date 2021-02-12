//Alondra Sánchez Molina
//Jerarquia de procesos, cada vez que queramos crear un hermano se vuelve a confirmar si estamos dentro del padre

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main() { //R
	pid_t pidM, pidL, pidQ, pidA, pidZ, pidN, pidS, pidK, pidG, pidD, pidB;
	int status;
	
	pidM=fork();
	if(pidM==0){//M
		printf("Soy el proceso M y mi ID es: %d y el ID de mi padre es: %d\n", getpid(), getppid());
		pidQ=fork();
		wait(&status);
		if(pidQ==0){//Q
			printf("Soy el proceso Q y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
		}else if (pidQ>0){//M
			pidA=fork();
			wait(&status);
			if(pidA==0){//A
				printf("Soy el proceso A y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
				pidZ=fork();
				wait(&status);
				if(pidZ==0){//Z
					printf("Soy el proceso Z y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
				}else if(pidZ>0){//A
					pidN=fork();
					wait(&status);
					if(pidN==0){//N
						printf("Soy el proceso N y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
						pidS=fork();
						wait(&status);
						if(pidS==0){//S
							printf("Soy el proceso S y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
						}
					}
				}
			}
		}
	}else if(pidM>0){//R
		printf("Soy el proceso R y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
		pidL=fork();
		wait(&status);
		if(pidL==0){//L
			printf("Soy el proceso L y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
			pidK=fork();
			wait(&status);
			if(pidK==0){//K
				printf("Soy el proceso K y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
			}else if(pidK>0){//L
				pidG=fork();
				wait(&status);
				if(pidG==0){//G
					printf("Soy el proceso G y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
					pidB=fork();
					wait(&status);
					if(pidB==0){//B
						printf("Soy el proceso B y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
					}
				}else if(pidG>0){//L
					pidD=fork();
					wait(&status);
					if(pidD==0){//D
						printf("Soy el proceso D y mi ID es: %d y el ID de mi padre es: %d\n" , getpid(), getppid());
					}
				}
			}	
		}
	}
}
