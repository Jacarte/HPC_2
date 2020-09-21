

#include <stdio.h>


int time_delta;
int n;
int *initial_position;
int *initial_velocity;
int T;

int main(void){

	printf("Set input data as follows: <number of particles> <delta_time> <Time> <for each particle <mass> <x0> <y0> <vx0> <vy0>>\n");
	scanf("%d %d %d", &n, &time_delta, &T);

	initial_position = (int*) malloc(sizeof(int)*n*2);
	initial_velocity = (int*) malloc(sizeof(int)*n*2);

	for(int i = 0; i < n; i++){
		// Components should be stored one at a side, it would be better to load
		scanf("%d %d %d %d", &initial_position[i], &initial_position[i + 1], &initial_velocity[i], &initial_velocity[i + 1]); 
	}

	#ifdef DEBUG

	for(int i = 0; i < n; i++){
		printf("Positions\n\t%d %d\n", initial_position[i], initial_position[i + 1]);
	}

	for(int i = 0; i < n; i++){
		printf("Velocities\n\t%d %d\n", initial_velocity[i], initial_velocity[i + 1]);
	}

	#endif

	#ifdef DEBUG1
	printf("Processing...\n");
	#endif

	for(int i = 1; i <= T; i++){
		int time_step = i*time_delta;

		if(i == T){
			printf("Simulation results\n idx - (postion) (velocity)\n");

			for(int i = 0; i < n; i++){
				printf("%d - (%d, %d)  (%d, %d)", i, initial_position[i], initial_position[i + 1], initial_velocity[i], initial_velocity[i + 1]);
			}
			printf("\n");
		}
	}

	free(initial_position);
	free(initial_velocity);

	return 0;
}