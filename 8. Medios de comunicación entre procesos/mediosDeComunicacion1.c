//Mecanismos de comunciación. PIPE Y FIFO

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <fcntl.h>

struct data{
	float x;
	int y;
	char cad[20];
};

int main(int argc, char **argv){ //A
	int n, i;
	int fdpipe[2], fdFifo;
	
	n=atoi(argv[1]);
	pid_t pidB;
	
	struct data nStruct[n];
	pipe(fdpipe);
	
	char *mififo = "/home/alondra/Escritorio/Programas S.O. I/15. Medios de comunicación entre procesos/mififo"; 
	mkfifo(mififo, 0666); 

	pidB=fork();
	if(pidB==0){ //B
		for(i=0;i<n;i++){
			printf("\nEstructura %d: \n",i+1);
			printf("Ingrese el valor de x: ");
			scanf("%f",&nStruct[i].x);
			printf("Ingrese el valor de y: ");
			scanf("%d",&nStruct[i].y);
			printf("Ingrese la cadena: ");
			getchar();
			scanf("%[^\n]",nStruct[i].cad);
		}	
		write(fdpipe[1],&nStruct,sizeof(nStruct));
	}
	if(pidB>0){  //A
		read(fdpipe[0],&nStruct,sizeof(nStruct));
		/*for(i=0;i<n;i++){
			printf("\nPIPE datos de la estructura no.%d son:\n", i+1);
			printf("%.2f\n",nStruct[i].x);	
			printf("%d\n",nStruct[i].y);	
			printf("%s\n",nStruct[i].cad);	
		}*/
		fdFifo = open(mififo, O_WRONLY); 
		write(fdFifo,&nStruct,sizeof(nStruct));  
	}
}

