#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){


	if(argc != 2){
		perror("Uso de argumentos incorrecto: ./ejercicio entero \n");
		exit (-1);
	}

	int num = atoi(argv[1]);

	pid_t pid;

	if((pid=fork())<0){

		perror("\nError en el fork");
		exit(-1);

	}else	if(pid==0){	// Proceso hijo

				if (num%2==0)
					printf("El numero %d es par\n", num);
				else
					printf("El numero %d es impar\n", num);

			}else{		// Proceso padre
				
				if (num%4==0)
					printf("El numero %d es divisible por 4\n",num);
				else
					printf("El numero %d no es divisible por 4\n",num);
			}

	return 0;
}