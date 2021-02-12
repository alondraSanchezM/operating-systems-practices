//Servidor de archivos

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <errno.h>

char filename[50];

struct arch{
	long idMensaje;
	int tamArchivo;
	int id;
	int pid;
	char nombre[50];
	char *datos;
}arch;


int main(int argc, char *argv[]) {

	key_t key;
	int n;
	int idQueue,df,nbytes;
	char *buff,aux;
	n=atoi(argv[1]);
	
	struct arch msg;
	struct stat buf;

	key = ftok (".", 'e');
	if (key == (key_t)-1){
		printf("Error al obtener clave para cola mensajes\n");
		exit(1);
	}

	idQueue= msgget (key, 0600 | IPC_CREAT);
	if (idQueue == -1){
		printf("Error al obtener identificador para cola mensajes\n");
		exit (1);
	}

	for (int i = 0; i < n; i++){
		msgrcv (idQueue, (struct msgbuf *)&msg, sizeof(struct arch), i+1, 0);

		printf("Datos recibidos\n");
		printf("Nombre del archivo:  %s \n",msg.nombre);
		printf("Tamaño del Archivo enviado: %d \n",msg.tamArchivo);
		//printf("Id del proceso %d\n", msg.pid);

		strcpy (filename, msg.nombre);
		printf("\nBuscando archivo %s en el directorio\n",filename);

		//Comprobar que existe en el directorio
	  	df = open(filename,O_RDONLY);
	  	if(df == -1){
	    	printf("\nError - Archivo %s no encontrado en el directorio.\n", filename);
	    	exit(-1);
	  	}
		if (stat(filename, &buf) == -1){	
			perror(filename);
			exit(-1);
		}
		else{
			printf("Archivo %s encontrado, su tamaño es de: %d bytes.\n\n",filename,buf.st_size);
		}

		struct archivoEncontrado{
			long idMensaje;
			char datos[buf.st_size];
		}reci;

		reci.idMensaje=i+20;
	    
	  	for(int i=0; i<buf.st_size; i++){
	    	nbytes=read(df,&aux,sizeof(aux));
	    	 reci.datos[i]=aux;
	  	}
    	//printf("\nEl contenido del archivo solicitado es: \n%s\n", reci.datos);
	  	msgsnd(idQueue, (struct msgbuf *)&reci, sizeof(struct archivoEncontrado),IPC_NOWAIT);

	}
}

