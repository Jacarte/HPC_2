

GCC=${CC}

CCFLAGS=-fopenmp

hello.out: hello.c
	${GCC} ${CCFLAGS} -DNUM_THREADS=20 hello.c -o hello.out


stream.out: stream.c
	${GCC} ${CCFLAGS} -DNTIMES=5 stream.c -o stream.out


clean:
	rm *.out