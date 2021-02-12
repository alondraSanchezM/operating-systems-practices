//Cliente del servidor con cola de mensajes 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
	int idQueue,df;
	
	struct arch msg;
	struct stat buf; 
	
	key = ftok (".", 'e');
	if (key == (key_t)-1){
		printf("Error al obtener la clave \n");
		exit (1);
	}

	idQueue = msgget (key, 0600 | IPC_CREAT); 
	if (idQueue == -1){
		printf("Error al obtener el identificador de mensaje \n");
		exit (1);
	}

	printf("\nCantidad de archivos a leer: ");
  	scanf(" %d",&n);

	for (int i = 0; i<n; i++){
		printf("\nNombre del archivo: ");
	  	scanf(" %[^\n]",filename);

	  	df = open(filename,O_RDONLY);
	  	if(df == -1){
	    	printf("\nError - Archivo %s no encontrado en el directorio.\n", filename);
	    	exit(-1);
	  	}
		if (stat(filename, &buf) == -1){	
			perror(filename);
			exit(-1);
		}

		msg.idMensaje = i+1;
		msg.id = key;
		strcpy (msg.nombre, filename); 
		msg.tamArchivo = buf.st_size;  

		msgsnd (idQueue, (struct msgbuf *)&msg,sizeof(struct arch), IPC_NOWAIT); 

		struct archivoEncontrado{
			long idName;
			char datos[buf.st_size];
		}reci;

	    msgrcv(idQueue,(struct msgbuf *)&reci,sizeof(struct archivoEncontrado),i+11,0);

    	printf("\nEl contenido del archivo solicitado es: \n%s\n", reci.datos);
	}
 	msgctl(idQueue, IPC_RMID, (struct msqid_ds *)NULL);
}
