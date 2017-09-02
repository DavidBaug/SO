/*#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]){

	DIR *direct;
	unsigned int permisos;
	char *pathname;
	struct stat atributos;
	struct dirent *ed;
	char cadena[100];
	char cadena2[100];
	extern int errno;
	
	if (argc==3){
		pathname=argv[1];
		direct=opendir(pathname);
		permisos=strtol(argv[2],NULL,8);
	}else{
		printf("Uso: ejercicio2.c <pathname> <permisos>\n");
		exit(-1);
	}

	readdir(direct);
	
	while((ed=readdir(direct))!=NULL){
		sprintf(cadena,"%s/%s",pathname,ed->d_name);
		if(stat(cadena,&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de archivo");
			perror("\nError en lstat");
			exit(-1);
		}
		if(S_ISREG(atributos.st_mode)){
			sprintf(cadena2,"%s",ed->d_name);
			printf("%s: %o ",cadena2,atributos.st_mode);
			chmod(cadena,permisos);

			if(chmod(cadena,permisos) < 0)
				printf("Error: %s\n",strerror(errno));
			else{
				stat(cadena,&atributos);
				printf("%o \n",atributos.st_mode);
			}
		}
	}
}*/




#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void listarPermisos(struct stat atributos){
	if(S_ISREG(atributos.st_mode)!=0) printf("-");
    if(S_ISDIR(atributos.st_mode)!=0) printf("d");
   	if(S_ISLNK(atributos.st_mode)!=0) printf("l");
   	if(S_ISCHR(atributos.st_mode)!=0) printf("c");
   	if(S_ISBLK(atributos.st_mode)!=0) printf("b");
    if(S_ISFIFO(atributos.st_mode)!=0) printf("t");
    if(S_ISSOCK(atributos.st_mode)!=0) printf("s");

	//Permisos
    if((atributos.st_mode & S_IRUSR)!=0) printf("r");
	else{printf("-");}
     		
	if((atributos.st_mode & S_IWUSR)!=0) printf("w");
    else{printf("-");}
     	
    if((atributos.st_mode & S_IXUSR)!=0) printf("x");
    else{printf("-");}
     
    if((atributos.st_mode & S_IRGRP)!=0) printf("r");
}

int main(int argc, char *argv[]){ 
	DIR *dirp; 

  	struct dirent *direntp; 
  	struct stat atributos; 
  	int count = 0; 
  	int tamanioTotal = 0; 

  	if(argc<2){ 
    	printf("\nSintaxis de la ejecucion erronea: Ejercicio2 [<nombre del directorio>][<mascara en octal>]"); 
     	exit(-1); 
  	} 

  	dirp = opendir(argv[1]); 

  	if(dirp==NULL){ 
    	printf("\nError no se pudo abrir el directorio: "); 
    	exit(-1); 
  	} 
  
  	printf(" Los i-nodos son: "); 

  	while ((direntp=readdir(dirp))!=NULL){ 
    	if (direntp->d_name == "." || direntp->d_name == ".."){ 
        	printf("\nNombre: %s",direntp->d_name); 
    	}else{ 
			if (lstat(direntp->d_name,&atributos) < 0) { 
	  			printf("\nError al intentar acceder a los atributos de %s",direntp->d_name); 
	   			perror("\nError en lstat"); 
			}else{ 
				if(S_ISREG(atributos.st_mode)!=0 && (atributos.st_mode & S_IXGRP)!=0 && (atributos.st_mode & S_IXOTH)!=0){ 
              		printf("\n%s %d",direntp->d_name,(int)direntp->d_ino); 
              		count++; 

              		tamanioTotal += atributos.st_size; 
	  			} 
         	} 
    	}      
  	} 
  
  	closedir(dirp); 

  	printf("\nExisten %d archivos regulares con permisos x para grupos y otros",count); 
  	printf("\nEl tamaño total ocupado por esos archivos es %d \n",count); 

} 

