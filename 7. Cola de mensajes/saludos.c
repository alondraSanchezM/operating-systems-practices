//Saludo entre padre e hijo mediante una cola

#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct msgbuf{
	long type;
	int edad;
	char mytxt[25];
}mybuf;

int main(int argc, char *argv[]){
	int queue_id;
	pid_t pid;
	key_t key;
	
	key=ftok(".",'s');
	queue_id=msgget(key, 0777 | IPC_CREAT);
	
	pid=fork();
	if(pid==0){
		mybuf.type= 1;
		strcpy(mybuf.mytxt, "Hola padre");
		mybuf.edad=atoi(argv[1]);
		msgsnd(queue_id, (struct msgbuf *)&mybuf, sizeof(mybuf.type)+sizeof(mybuf.mytxt)+sizeof(mybuf.edad),IPC_NOWAIT);
		msgrcv(queue_id, (struct msgbuf *)&mybuf, sizeof(mybuf.type)+sizeof(mybuf.mytxt)+sizeof(mybuf.edad),2,0);
		printf("%s,", mybuf.mytxt);
		printf(" mi edad es: %d\n", mybuf.edad);
	}else if(pid>0){
		mybuf.type= 2;
		mybuf.edad=atoi(argv[2]);
		strcpy(mybuf.mytxt, "Hola hijo");
		msgsnd(queue_id, (struct msgbuf *)&mybuf, sizeof(mybuf.type)+sizeof(mybuf.mytxt)+sizeof(mybuf.edad),IPC_NOWAIT);
		msgrcv(queue_id, (struct msgbuf *)&mybuf, sizeof(mybuf.type)+sizeof(mybuf.mytxt)+sizeof(mybuf.edad),1,0);
		printf("%s, ", mybuf.mytxt);		
		printf("mi edad es: %d\n", mybuf.edad);
		wait(NULL);
	}
	msgctl(queue_id, IPC_RMID, 0);
}
