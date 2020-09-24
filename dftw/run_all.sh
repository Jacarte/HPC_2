pads="256"
echo "t, NTHREADS, TIME,NTHREADS, TIME,NTHREADS, TIME,NTHREADS, TIME,NTHREADS, TIME,NTHREADS, TIME,NTHREADS, TIME,NTHREADS, TIME,NTHREADS, TIME,NTHREADS, TIME"
for t in $(seq 1 100)
do
	for p in $pads 
		do
		threads="1 2 4 8 12 16 20 24 28 32"
		echo -n $t
		for i in $threads
		do
			echo -n ','
			export DEF="-DNTHREADS=$i -DONLY_TIME -DPAD=$p -DCOMPONENTS=10000"
			make clean 1>/dev/null 2> /dev/null
			make 1>/dev/null 2> /dev/null
			o=$(./DFTW_1.out )
			echo -n $i,$o
		done

		echo
	done
done