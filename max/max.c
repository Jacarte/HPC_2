#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <omp.h>

#define N 10000000
#define MAX 20000

#define NTHREADS 32
#define NTRIES 2
#define PAD 512

double maxval = 0.0; 
int maxloc = 0;
double x[N];

typedef struct {
	double val;
	int loc;
	char padding[PAD];
} MAXINFO;

void init_array(){
	srand(time(0)); // seed
   for(int i=0; i < N;i++){
     // Generate random number between 0 and 1
     x[i] = ((double)(rand()) / MAX)*((double)(rand()) / MAX)*((double)(rand()) / MAX)*MAX;
   }
}

// linear max
int max(){

	for (int i=0; i < N; i++){
		if (x[i] > maxval)  {
			maxval = x[i]; maxloc = i;
		}
	}
}


// parallel max
int maxOmpNoCriticalSection(){

	omp_set_num_threads(NTHREADS);

	#pragma omp parallel for
	for (int i=0; i < N; i++){
		if (x[i] > maxval) {
			maxval = x[i]; maxloc = i;
		}
		
	}
	
}

// max with critical section
int maxOmpCriticalSection(){

	omp_set_num_threads(NTHREADS);

	#pragma omp parallel for
	for (int i=0; i < N; i++){
		#pragma omp critical 
		{
			if (x[i] > maxval) {
				maxval = x[i]; maxloc = i;
			}
		}
	}
	
}

// max value per thread
double maxValues[NTHREADS];
int maxLocs[NTHREADS];

int maxOmpTempIndexes(){

	omp_set_num_threads(NTHREADS);

	int th_id;

	#pragma omp parallel for private(th_id)
	for (int i=0; i < N; i++){
		th_id = omp_get_thread_num();
		
		if (x[i] > maxValues[th_id]) {
			maxValues[th_id] = x[i]; maxLocs[th_id] = i;
		}
		
	}

	for(int i = 0; i < NTHREADS; i++)
		if (maxValues[i] > maxval) {
				maxval = maxValues[i]; maxloc = maxLocs[i];
		}
}


// false sharing and padding
MAXINFO infos[NTHREADS];

int maxOmpTempIndexesPadding(){

	omp_set_num_threads(NTHREADS);

	int th_id;

	#pragma omp parallel for private(th_id)
	for (int i=0; i < N; i++){
		th_id = omp_get_thread_num();
		
		if (x[i] > infos[th_id].val) {
			infos[th_id].val = x[i]; infos[th_id].loc = i;
		}
		
	}

	for(int i = 0; i < NTHREADS; i++)
		if (infos[i].val > maxval) {
				maxval = infos[i].val; maxloc =infos[i].loc;
		}
}


int main(void){
	
	double start_time,run_time;  


	init_array();
	start_time = omp_get_wtime(); 
	for(int i = 0; i < NTRIES; i++) 
	 #ifdef SERIAL 
	 	max(); 
	 #endif
	 #ifdef OMP1
	 	maxOmpNoCriticalSection();
	 #endif
	
	 #ifdef OMP2
		maxOmpCriticalSection();
	 #endif

	
	 #ifdef OMP3
		maxOmpTempIndexes();
	 #endif

	 #ifdef OMP4
		maxOmpTempIndexesPadding();
	 #endif

	run_time = omp_get_wtime() - start_time;
	
	printf("%f %d  %.6f\n", maxval, maxloc, run_time/(double)NTRIES);

}

