

GCC=${CC}

CCFLAGS=-fopenmp

hello.out: hello.c
	${GCC} ${CCFLAGS} -DNUM_THREADS=20 hello.c -o hello.out

clean:
	rm *.out