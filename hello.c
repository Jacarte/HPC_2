#include <stdio.h>

int th_id, nthreads;


int main(void){


	#pragma omp parallel private(th_id)
	{
		nthreads = omp_get_num_threads();	

    	th_id = omp_get_thread_num();
		printf("Hello, world %d/%d. \n", th_id, nthreads);
	}

	return 0;
}