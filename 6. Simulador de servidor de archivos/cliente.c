//CLiente: envia nombre del archivo de texto e id del proceso
//imprime en pantalla el archivo.c

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
char  *ptrArchivo; 
    
void manejador(int s){
	
	printf("\n\nArchivo recibido:\n ");
	printf("%s\n",ptrArchivo);

}

int main(int argc, char *argv[]){

	struct sigaction act;
	struct stat infoArchivo;
	
	int idSegE, idSegT;
	key_t keyE, keyT;

	act.sa_handler=manejador;	
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;	
	
	printf("Ingrese el nombre del archivo: ");
	scanf("%s", datos.archivo);
	
    stat(datos.archivo, &infoArchivo);   

	keyE = ftok(".",'e'); 
	keyT = ftok(".",'t'); 
	
	idSegE = shmget(keyE,sizeof(struct DATA),IPC_CREAT | 0777);
  	idSegT = shmget(keyT, infoArchivo.st_size,IPC_CREAT | 0777);
  	ptr = (struct DATA *)shmat(idSegE,0,0);
	ptrArchivo = (char *)shmat(idSegT,0,0);

	printf("\nID: %d Archivo solicitado: %s\n",getpid(),datos.archivo);
	
	datos.id=getpid();
	*ptr = datos;
	strcpy(ptrArchivo,datos.archivo);

	sigaction(SIGUSR1, &act, NULL);
	pause();
	
	shmdt(ptrArchivo);
	shmctl(idSegT,IPC_RMID,NULL);
	shmdt(ptr);
	shmctl(idSegE,IPC_RMID,NULL);
}
