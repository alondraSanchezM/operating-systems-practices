#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(){

  pid_t pid;
  key_t key1,key2;
  int n,id1,id2,aux;
  int *ptr1, *ptr2;

  pid=fork();

if(pid == 0){ //Hijo
    sleep(3);
    key1 = ftok(".",'a');
    id1=shmget(key1,sizeof(int),0);
    printf("\nZona de memoria reconocida ID: %d", id1);
    ptr1 = (int *)shmat(id1,0,0);
    aux = *ptr1;
    printf("\nLeido: %d\n",aux);
    shmdt(ptr1);
    shmctl(id1,IPC_RMID,NULL);
    printf("Zona de memoria liberada.\n");
}

if(pid>0){  //Padre
    printf("\nIntroduce un entero: ");
    scanf("%d",&n);
    key2 = ftok(".",'a');
    id2=shmget(key2,sizeof(int),IPC_CREAT | 0777);
    printf("\nZona de Memoria creada con ID: %d", id2);
    ptr2 = (int *)shmat(id2,0,0);
    *ptr2 = n;
    printf("\nMemoria reservada.\n");
  }

}
