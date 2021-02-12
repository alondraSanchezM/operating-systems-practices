#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

typedef struct DATA{
  int n;
  char c;
}DATA;


int main(){
  int id;
  key_t key;
  struct DATA aux, *ap;

  key = ftok(".",'e');
  id = shmget(key,sizeof(DATA),0);
  ap = (DATA *)shmat(id,0,0);
  aux = *ap;
  printf("\nDatos en segmento de memoria: %d y %c\n",aux.n,aux.c);

  for(int i=0;i<aux.n;i++)
  	printf("%c\n",aux.c );

  shmdt(ap);
  shmctl(id,IPC_RMID,NULL);
}
