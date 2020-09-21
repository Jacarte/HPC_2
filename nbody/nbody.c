

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
		scanf("%d %d", &initial_position[i], &initial_position[i + 1]);
	}

	for(int i = 0; i < n; i++){
		scanf("%d %d", &initial_velocity[i], &initial_velocity[i + 1]);
	}


	for(int i = 0; i < n; i++){
		printf("\t%d %d\n", initial_velocity[i], initial_velocity[i + 1]);
	}

	free(initial_position);
	free(initial_velocity);
	printf("Processing...\n");
		
	return 0;
}