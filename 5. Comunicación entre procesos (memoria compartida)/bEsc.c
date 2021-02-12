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
  int num,id;
  char car;
  
  key_t key;
  struct DATA est, *ap;
  
  printf("\nIngrese un entero: ");
  scanf("%d",&est.n);
  fflush(stdin);
  printf("\nIngrese un caracter: ");
  scanf(" %c", &est.c);
  printf("\nDatos ingresados: %d y %c",est.n, est.c );

  key = ftok(".",'e');
  id = shmget(key,sizeof(DATA),IPC_CREAT | 0777);
  ap = (DATA *)shmat(id,0,0);
  *ap = est;
  printf("\nID de segmento: %d\n", id);
}
