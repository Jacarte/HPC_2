

GCC=${CC}

CCFLAGS=-fopenmp

hello.out: hello.c
	${GCC} ${CCFLAGS} hello.c -o hello.out

clean:
	rm *.out