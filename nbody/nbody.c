

#include <stdio.h>
#include <math.h>

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

int main(void){

	printf("Set input data as follows: <number of particles> <delta_time> <Time> <for each particle <mass> <x0> <y0> <vx0> <vy0>>\n");
	scanf("%d %lf %d", &n, &time_delta, &T);

	position = (vect_t*) malloc(sizeof(vect_t)*n);
	velocity = (vect_t*) malloc(sizeof(vect_t)*n);
	forces = (vect_t*) malloc(sizeof(vect_t)*n);
	masses = (double*) malloc(sizeof(double)*n);

	for(int i = 0; i < n; i++){
		scanf("%lf %lf %lf %lf %lf", &masses[i], &position[i][0], &position[i][1], &velocity[i][0], &velocity[i][1]); 
	}

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

	for(int i = 1; i <= T; i++){
		int time_step = i*time_delta;



		for(int q = 0; q < n; q++){
			forces[q][0] = 0; 
			forces[q][1] = 0; 
		}

		for(int q = 0; q < n; q++){
			for(int k = 0; k < n; k++){
				if(k > q){
					double xdiff = position[q][0] - position[k][0];
					double ydiff = position[q][1] - position[k][1];

					double dist = sqrt(xdiff*xdiff + ydiff*ydiff); 
            		double dist_cubed = dist*dist*dist; 

					double x_force = G*masses[q]*masses[k]/dist_cubed * xdiff; 
					double y_force = G*masses[q]*masses[k]/dist_cubed * ydiff; 
					

					forces[q][1] += y_force; 
					forces[k][0] -= x_force; 
					forces[k][1] -= y_force;
					forces[k][0] += x_force;
				}
			}
		}

		if(i == T){
			printf("Simulation results\n idx - (postion) (velocity)\n");

			for(int i = 0; i < n; i++){
				printf("%d - (%lf, %lf)  (%lf, %lf)", i, position[i][0], position[i][1], velocity[i][0], velocity[i][1]);
			}
			printf("\n");
		}
	}

	free(position);
	free(velocity);
	free(forces);
	free(masses);
	return 0;
}