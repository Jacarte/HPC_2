

GCC=${CC}

CCFLAGS=-fopenmp


stream.out: stream_template.c
	cp stream_template.c stream.c
	sed -i -e "s/%SCHEDULE%/${SCHEDULE}/g" stream.c
	${GCC} ${CCFLAGS} -DNTIMES=25 stream.c -o stream.out


clean:
	rm *.out