

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define DIM 2
typedef double vect_t[DIM];

#define G 6.673e-11

double time_delta;
int n;
vect_t *position;
vect_t *velocity;
vect_t *forces;
double *masses;
int T;

int init(){

	for(int i = 0; i < n; i++){
		position[i][0] = (rand()/(double)(RAND_MAX))*2 - 1;
		position[i][1] = (rand()/(double)(RAND_MAX))*2 - 1;


		velocity[i][0] = (rand()/(double)(RAND_MAX))*2 - 1;
		velocity[i][1] = (rand()/(double)(RAND_MAX))*2 - 1;

		masses[i] = fabs((rand()/(double)(RAND_MAX))*2 - 1);
	}
	return 0;
}

int main(void){

	#ifndef MEASURE_TIME
	printf("Set input data as follows: <number of particles> <delta_time> <Time> <for each particle <mass> <x0> <y0> <vx0> <vy0>>\n");
	#endif
	scanf("%d %lf %d", &n, &time_delta, &T);

	position = (vect_t*) malloc(sizeof(vect_t)*n);
	velocity = (vect_t*) malloc(sizeof(vect_t)*n);
	forces = (vect_t*) malloc(sizeof(vect_t)*n);
	masses = (double*) malloc(sizeof(double)*n);

	#ifdef RANDOM_INIT
		init();
	#else
		
		for(int i = 0; i < n; i++){
			scanf("%lf %lf %lf %lf %lf", &masses[i], &position[i][0], &position[i][1], &velocity[i][0], &velocity[i][1]); 
		}

	#endif
	
	#ifdef DEBUG

	for(int i = 0; i < n; i++){
		printf("Positions\n\t%lf %lf\n", position[i][0], position[i][1]);
	}

	for(int i = 0; i < n; i++){
		printf("Velocities\n\t%lf %lf\n", velocity[i][0], velocity[i][1]);
	}

	#endif

	#ifdef DEBUG1
	printf("Processing...\n");
	#endif

	#ifdef MEASURE_TIME
	double t1, t2;  
	t1 = omp_get_wtime(); 
	#endif

	for(int i = 1; i <= T; i++){
		int time_step = i*time_delta;

		for(int q = 0; q < n; q++){
			for(int d = 0 ; d < DIM; d++)
				forces[q][d] = 0; 
		}

		#pragma omp parallel for schedule(static, 100)
		for(int q = 0; q < n; q++){
			for(int k = 0; k < n; k++){
				#ifdef REDUCED
				if(k > q){
				#else
				if (k != q) {
				#endif
				
					double xdiff = position[q][0] - position[k][0];
					double ydiff = position[q][1] - position[k][1];

					double dist = sqrt(xdiff*xdiff + ydiff*ydiff); 
					double dist_cubed = dist*dist*dist; 

					double x_force = G*masses[q]*masses[k]/dist_cubed * xdiff; 
					double y_force = G*masses[q]*masses[k]/dist_cubed * ydiff; 
					
	
					#ifdef DEBUG1

    					int th_id = omp_get_thread_num();
						printf("Processing...%d\n", th_id);
					#endif


					forces[k][0] -= x_force; 
					forces[k][1] -= y_force;

					#ifdef REDUCED

					forces[q][1] += y_force; 
					forces[q][0] += x_force;
					#endif

				}
			}
			

			position[q][0] += time_delta*velocity[q][0]; 
			position[q][1] += time_delta*velocity[q][1]; 

			velocity[q][0] += time_delta/masses[q]*forces[q][0]; 
			velocity[q][1] += time_delta/masses[q]*forces[q][1];
			
		}

		// print general stats
		if(i == T){

			#ifdef MEASURE_TIME
			t2 = omp_get_wtime(); 
			printf("%d %f %d %.6f\n", n, time_delta, T, (t2 - t1));
			#else
			printf("Simulation results\n idx - (postion) (velocity)\n");

			for(int i = 0; i < n; i++){
				printf("%d - (%lf, %lf)  (%lf, %lf)\n", i, position[i][0], position[i][1], velocity[i][0], velocity[i][1]);
			}
			printf("\n");
			#endif
		}
	}

	free(position);
	free(velocity);
	free(forces);
	free(masses);
	return 0;
}