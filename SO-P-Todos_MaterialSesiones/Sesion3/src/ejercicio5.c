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

	int estado, hijos, i;
	
	hijos = atoi(argv[1]);

	pid_t PID[hijos];
		
	//Vaciar el buffer para evitar errores en la salida
	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf") ;
	}

	for(i=0; i < hijos; i++){
		if( (PID[i]=fork())<0) {
			perror("\nError en el fork" ) ;
			exit(-1);
		}else if(PID[i]==0) { //proceso hijo ejecutando el programa
			printf("Soy el hijo %d\n", getpid()); fflush(stdout);
			exit(0);
		}
	}

	int auxHijos = hijos; // Si modificaba hijos en un bucle en el otro no entraria porque esta como condicion (i<hijos)

	for(i=0; i<hijos; i = i +2){ //Impar --> 0+1, 2+1...
		waitpid(PID[i],&estado);
		printf("\nAcaba de finalizar mi hijo con PID = %d y estado %d\n",PID[i], estado); fflush(stdout);
		printf("Solo me quedan %d hijos vivos, este es el %do hijo.\n", auxHijos, i+1);
		auxHijos--;
	}
	for(i=1; i<hijos-1; i = i +2){ // Par
		waitpid(PID[i],&estado);
		printf("\nAcaba de finalizar mi hijo con PID = %d y estado %d\n",PID[i], estado); fflush(stdout);
		printf("Solo me quedan %d hijos vivos, este es el %do hijo.\n", auxHijos, i+1);
		auxHijos--;
	}
	exit(0);
}