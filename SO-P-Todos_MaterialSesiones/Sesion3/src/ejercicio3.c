#include <sys/types.h>
#include <unistd.h>		
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{

	if (argc!=2){
		perror("Uso: ./ejercicio nprocesos");
	}

	int nprocs=atoi(argv[1]);
	int i;
	
	pid_t childpid[nprocs];

	/*
	Jerarquía de procesos tipo 1
	*/

	for (i=1; i < nprocs; i++) {
		if ((childpid[i]= fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}

		if (childpid[i]==0){
			printf("\nJerarquía 1\n"); fflush(stdout);
			printf("Identificador de proceso: %d\n", getpid());
			printf("Identificador del proceso padre: %d\n", getppid());
		}
	}

	
	/*
	Jerarquía de procesos tipo 2
	*/

	for (i=1; i < nprocs; i++) {
		if ((childpid[i]= fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}

		if (childpid[i]!=0){
			printf("\nJerarquía 2\n"); fflush(stdout);
			printf("Identificador de proceso: %d\n", getpid());
			printf("Identificador del proceso padre: %d\n", getppid());
		}
	}
}