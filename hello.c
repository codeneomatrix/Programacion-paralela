#include "omp.h"
#include <stdio.h>
// gcc -fopenmp -o hello hello.c
void main(){
	omp_set_num_threads (2);  // numero de hilos a utilizar por defecto
	#pragma omp parallel //
	{
		int ID = omp_get_thread_num();
		printf("hello <%d>  \n", ID );
		printf("world <%d>  \n", ID );
	}
}