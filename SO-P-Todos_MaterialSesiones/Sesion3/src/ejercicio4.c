#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	if (argc != 2){
		perror("Uso: ./ejercicio nHijos");
		exit (-1);
	}

	int i, hijos, estado;
	pid_t PID;

	hijos = atoi(argv[1]);
	
	// Creación procesos hijos
	
	for(i=0; i<hijos; i++){
		if((PID = fork())<0){
			perror("Error en fork\n");
			exit(-1);
		}
	
		if(PID==0){
			printf("\nSoy el hijo PID = %i\n", getpid());
			exit(0);
		}
	}

	// Se espera a que finalice la ejecución del hijo

	for(i=(hijos-1); i>=0; i--){
		PID = wait(&estado);
		printf("\nHa finalizado mi hijo con PID = %i\n", PID);

		if (i==0)
			printf("Todos mis hijos han muerto :(\n\n");
		else
			printf("Solo me quedan %i hijos vivos\n", i);
	}

	exit(0);

}