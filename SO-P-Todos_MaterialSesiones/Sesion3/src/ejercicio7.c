#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int estado;
	
	if(argc<2 && argc%3!=0){
		printf("Uso: ./ejercicio programa orden(bg/fg) \n"); //No ponemos & porque eso afectaría al propio proceso y no a la ejecución del
		exit(-1);											 // programa que ejecuta el proceso hijo	
	}
	
	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(-1);
	}else if(pid==0) {
		for (int i = 1; i <= argc; ++i){
			if (argv[i+1]=="bg"){
				if( (execl(argv[1] , '&',NULL)<0)) {		// En teoría funciona, pero el problema que tengo es si el programa
					perror("\nError en el execl");			// que va a ejecutar también necesita de parámetros al pasarlos no va
					exit(-1);								// a  ejecutar la orden
				}	
			}else{
				if( (execl(argv[1] ,NULL)<0)) {
					perror("\nError en el execl");
					exit(-1);
				}
			}
			
		}		
	}

	wait(&estado);
	printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado);
	exit(0);
}