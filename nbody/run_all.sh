

N="500 1000 2000"

echo "SERIAL"
for i in $N
do
	export CFLAGS="-DMEASURE_TIME $CFLAGS"
	make clean 1>/dev/null 2> /dev/null
	make 1>/dev/null 2> /dev/null
	
	./nbody.out <<< "$i 0.05 100"
done

echo "REDUCED"
for i in $N
do
	export CFLAGS="-DMEASURE_TIME -DREDUCED  $CFLAGS"
	make clean 1>/dev/null 2> /dev/null
	make 1>/dev/null 2> /dev/null
	
	./nbody.out <<< "$i 0.05 100"
done

echo "OMP"
export CC=gcc-9
for i in $N
do
	export CFLAGS="-DMEASURE_TIME -DREDUCED -fopenmp $CFLAGS"
	make clean 1>/dev/null 2> /dev/null
	make 1>/dev/null 2> /dev/null
	
	./nbody.out <<< "$i 0.05 100"
done

threads="1 4 8 12 16 20 24 28 32"

export CC=gcc-9

for t in $threads
do
	export  OMP_NUM_THREADS=$t
	for i in $N
	do
		export CFLAGS="-DMEASURE_TIME -DREDUCED -fopenmp $CFLAGS"
		make clean 1>/dev/null 2> /dev/null
		make 1>/dev/null 2> /dev/null
		
		echo -n "$t "
		./nbody.out <<< "$i 0.05 100"
	done
done