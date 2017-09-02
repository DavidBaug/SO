#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARCHIVO_FIFO "comunicacion"

int main(int argc, char *argv[]) {
	
	int inicio;
	int fin;
	int mitad;

	int numBytes;
	char buffer[80];

	char params[2];

	inicio=atoi(argv[1]);
	fin=atoi(argv[2]);

	mitad = inicio + ((fin - inicio) / 2);

	int fd1[2];
	int fd2[2];
	pid_t PID;

	pipe(fd1); //Llamada para crear un pipe
	pipe(fd2);

	if ((PID= fork())<0){
		perror("Error al hacer fork");
		exit(1);
	}

	if (PID == 0){
		
		close(fd1[0]);
		
		params[0] = inicio;
		params[1] = mitad;

		printf("paso 1\n");
		dup2(fd1[1],STDOUT_FILENO);
		execlp("esclavo","esclavo", params, NULL);

	}else{ // Si PID != 0 estamos en el proceso padre

		if (PID == 0){

			close(fd2[0]);

			params[0] = mitad + 1;
			params[1] = fin;
 
			printf("paso 2\n");
			dup2(fd2[1],STDOUT_FILENO);
			execlp("esclavo","esclavo", params,NULL);

			exit(0);

		}else{

			close(fd1[1]);
		
			numBytes= read(fd1[0],buffer,sizeof(buffer));
			
			dup2(fd1[0],STDIN_FILENO);

			printf("paso 3\n");
			
			while ((numBytes = read(fd1[0], &buffer, 4)) > 0){		
				printf("Valor: %d",1);
		 	}
		}
	}
	
	exit(0);
}
