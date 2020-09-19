#include <omp.h>
#include <stdio.h>

int th_id, nthreads;


int main(void){


	#ifdef NUM_THREADS
		omp_set_num_threads(NUM_THREADS);
	#endif

	#pragma omp parallel private(th_id)
	{


		nthreads = omp_get_num_threads();	

    	th_id = omp_get_thread_num();
		printf("Hello, world %d/%d. \n", th_id, nthreads);
	}

	return 0;
}
