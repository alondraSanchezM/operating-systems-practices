
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(){	
	printf("t\n");
	fork();
	printf("+\n");
	fork();
	printf("Q\n");
	fork();
	printf(".\n");
}
