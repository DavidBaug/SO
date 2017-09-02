/*
David Gil Bautista

45925324M

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>

int buscar_dir(DIR *direct, char pathname[], int *reg, int *tamanio, int nivel){
	
	struct stat atributos;
	struct dirent *ed;

	DIR *dirHijo;

	char cadena[500];
	int fd;
	char salida[] = "_sl";	

	int enlaces;

	pid_t pid;

	while((ed=readdir(direct)) != NULL){

		if (strcmp(ed->d_name, "..") != 0){
			sprintf(cadena,"%s/%s",pathname,ed->d_name);
			if(stat(cadena,&atributos) < 0) {
				printf("\nError al intentar acceder a los atributos de archivo");
				perror("\nError en lstat");
				exit(-1);
			}

			if (S_ISDIR(atributos.st_mode) && (nivel!=1)){			//Si encontramos directorio y estamos en el primer nivel

				if(pid = fork() < 0){									//Creamos hijo
					printf("Error al intentar crear hijo.\n");
					perror("Error en fork.\n");
				}else if (pid == 0){
					if ((dirHijo = opendir(cadena)) == NULL)						//Hijo ejecuta la funcion
						printf("\nError al abrir el directorio: [%s]\n", cadena);
					else
						enlaces+=buscar_dir(dirHijo, cadena, reg, tamanio,1);		//Sumamos a contador los enlaces que ha contado el hijo

				}

			}

			if (S_ISREG(atributos.st_mode)){

				if (atributos.st_mode.st_nlink > 1){		//Contador de enlaces duros
					enlaces+=atributos.st_mode.st_nlink;
					
					if (fd=open(sprintf(cadena,salida),O_CREAT|O_WRONLY|O_TRUNC|S_ISLNK) < 0){  //Creamos enlace simbolico
						printf("Error al crear enlace simbolico. \n");
						perror("Eror en open.");
						exit(-1);
					}else									//Si se crea el enlace simbolico borramos el archivo
						unlinkat(NULL,cadena,NULL);
				}
			}
		}
	}

	closedir(direct);

	return enlaces;
}

int main(int argc, char *argv[]){
	
	DIR *direct;
	char pathname[500];
	int reg = 0;
	int tamanio = 0;
	int contador = 0;

	struct sigaction sa;
	sa.sa_handler = SIGINT; // Ctrl + c


	if (argc==2){
		strcpy(pathname,argv[1]);
	}else{
		strcpy(pathname,".");
	}
	if((direct=opendir(pathname)) == NULL){
		printf("\nError al abrir directorio\n");
		exit(-1);
	}

	contador=buscar_dir(direct,pathname,&reg,&tamanio,0);

	if (sigaction(SIGINT,&sa,NULL)){
		printf("El numero de archivos con enlaces duros convertidos a enlaces simbolicos es %s\n",contador );
	}
	
	return 0;
}
