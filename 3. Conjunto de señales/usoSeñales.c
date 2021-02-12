//Alondra Sánchez Molina
//Este programa recibe una señal SIGINT

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

void manejador(){
	printf("Señal recibida\n");
}

int main(){
	printf("Mi ID ES %d\n", getpid());
	
	struct sigaction s;
	
	s.sa_handler=manejador;
	sigemptyset(&s.sa_mask);
	s.sa_flags=0;
	
	sigaction(SIGINT, &s, NULL);
	pause();
}
