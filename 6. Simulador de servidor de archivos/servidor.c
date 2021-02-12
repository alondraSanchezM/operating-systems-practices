//Servidor: envia archivo de texto al cliente y envia una señal que notifica al cliente que el archivo esta disponible. e=estrustura l=texto

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

struct DATA{
  int id;
  char archivo[50];
}datos, *ptr;


int main(){

	char *ptrArchivo; 
	int idSegE, idSegT, df; 
	
	struct stat infoArchivo;
	key_t keyE, keyT;
    
	keyE = ftok(".",'e'); 
	keyT = ftok(".",'t'); 
	
	idSegE = shmget(keyE,sizeof(struct DATA), IPC_CREAT | 0777);
  	ptr = (struct DATA *)shmat(idSegE,0,0);
	datos = *ptr;
	
	stat(datos.archivo,&infoArchivo);

	idSegT = shmget(keyT, infoArchivo.st_size, IPC_CREAT | 0777);
	ptrArchivo = (char *)shmat(idSegT,0,0);

	printf("Archivo solicitado: %s\nID recibido: %d\n",datos.archivo,datos.id);	

	char archi[infoArchivo.st_size];
	for (int i=0; i<strlen(datos.archivo);i++)
		archi[i]=datos.archivo[i];

	df=open(ptrArchivo,0);
	read(df, &archi, sizeof(archi));
	strcpy(ptrArchivo,archi);
	
	kill(datos.id,SIGUSR1);
}
