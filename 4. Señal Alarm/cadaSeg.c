//Este programa escribe y lee un dato cada segundo en datos2.dat

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#include<time.h> 

void manejadorLec(){
	int df, num;

	df=open("datosE.dat",0);
	read(df,&num,sizeof(num));
	printf("%d\n",num);
}

void manejadorEsc(){
	int df, num;
	srand(time(NULL)); 
	
	df=creat("datosE.dat",0777);
	df=open("datosE.dat",1);
	num=rand()%1000;
	write(df,&num,sizeof(num));
}

int main(){
	pid_t pid;
	
	struct sigaction act;
	pid=fork();
	
	if(pid==0){
		act.sa_handler=manejadorEsc;	
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;
		
		sigaction(SIGALRM,&act,NULL);
		
		for(;;){
			alarm(1);
		}

	}else if(pid>0){
		act.sa_handler=manejadorLec;	
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;
		
		sigaction(SIGALRM,&act,NULL);
		
		for(;;){
			alarm(1);
		}
	}
}
