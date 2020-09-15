#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <omp.h>

#define N 1000000
#define MAX 2000000

#define NTHREADS 32
#define NTRIES 1

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
int maxOmp(){

	omp_set_num_threads(NTHREADS);

	#pragma omp parallel 
	{
		#pragma omp parallel for
		for (int i=0; i < N; i++){
			#pragma omp critical {
				if (x[i] > maxval) {
					maxval = x[i]; maxloc = i;
				}
			}
		}
	}
}

int main(void){
	
	double t1, t2;  


	init_array();
	t1 = mysecond(); 
	for(int i = 0; i < NTRIES; i++) 
		max();
	t2 = mysecond();  

	printf("MAX %f, %d  %.6fs\n", maxval, maxloc, (t2 - t1)/(double)NTRIES);

	double baseline = maxval;
	double baselineloc =maxloc;

	t1 = mysecond();  

	for(int i = 0; i < NTRIES; i++) 
		maxOmp();
	t2 = mysecond();  

	if(maxval != baseline)
		exit(1);
	if(maxloc != baselineloc)
		exit(1);

	printf("MAX %f, %d %.6fs\n", maxval, maxloc, (t2 - t1)/(double)NTRIES);
}