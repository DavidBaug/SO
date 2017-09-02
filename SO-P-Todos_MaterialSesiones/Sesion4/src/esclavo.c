#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

	int inicio;
	int fin;

	inicio=atoi(argv[1]);
	fin=atoi(argv[2]);

	for (int n = inicio; n < fin; n++){
		int x;
		
		for (x = 2;x <= n-1; x++) {
			if ((n%x) == 0) 
				break; //No es primo, paramos la iteracion
		}
	
		if (x == n)
			printf("El numero %d es primo.\n", n);

	}

	exit(0);
}
