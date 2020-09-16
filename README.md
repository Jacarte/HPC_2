
## Exercise 1

Exercise 1 – OpenMP Hello World, get familiar with OpenMP Environment

1 -  Write an OpenMP [C code](hello.c) with each thread printing Hello World from Thread X! where X is the thread ID.

2 - Answers
  - To enable openmp in my local machine: ```gcc-9 -fopenmp```. Look at [README](README.md)
  - Ways to set the number of threads:
    - Before compiling ```export OMP_NUM_THREADS=<num_threads>```
	- In runtime ```omp_set_num_threads()```


Exercise 2 – STREAM

- Inside the folder stream, run ```bash run_stream.sh```. Ensure your **CC** flag is referencing an openmp-supporting compiler.
 

Exercise 3 – MAX

- Inside the folder max, run ```bash measure_all.sh```. Ensure your **CC** flag is referencing an openmp-supporting compiler.


The pdf report is in the folder report