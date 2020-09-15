#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <omp.h>

#define N 10000000
#define MAX 20000

#define NTHREADS 32
#define NTRIES 2

double maxval = 0.0; 
int maxloc = 0;
double x[N];


double mysecond(){  
	struct timeval tp;  
	struct timezone tzp;  
	int i;  i = gettimeofday(&tp,&tzp);  
	return ( 
		(double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );}

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


// linear max
int maxOmpNoCriticalSection(){

	omp_set_num_threads(NTHREADS);

	#pragma omp parallel for
	for (int i=0; i < N; i++){
		if (x[i] > maxval) {
			maxval = x[i]; maxloc = i;
		}
		
	}
	
}

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


int main(void){
	
	double t1, t2;  


	init_array();
	t1 = mysecond(); 
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
	t2 = mysecond();  

	printf("%f %d  %.6f\n", maxval, maxloc, (t2 - t1)/(double)NTRIES);

}