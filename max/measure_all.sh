

N=5

echo -n "data_serial = ["
for i in $(seq 1 $N)
do
	export DEF="-DSERIAL"
	make clean 1>/dev/null 2> /dev/null
	make max.out 1>/dev/null 2> /dev/null
	o=$(./max.out  | awk '{ print $3 }')
	echo -n $o,

done
echo "]"


echo -n "data_omp1= ["
for i in $(seq 1 $N)
do
	export DEF="-DOMP1 -DNTHREADS=32"
	make clean 1>/dev/null 2> /dev/null
	make max.out 1>/dev/null 2> /dev/null
	o=$(./max.out  | awk '{ print $3 }')
	echo -n $o,
done

echo "]"

threads="1 2 4 8 12 16 20 24 28 32"
echo -n "data_omp2= ["
for i in $threads
do
	export DEF="-DOMP2 -DNTHREADS=$i"
	make clean 1>/dev/null 2> /dev/null
	make max.out 1>/dev/null 2> /dev/null
	o=$(./max.out  | awk '{ print $3 }')
	echo -n $o,
done

echo "]"

threads="1 2 4 8 12 16 20 24 28 32"
echo -n "data_omp3= ["
for i in $threads
do
	export DEF="-DOMP3 -DNTHREADS=$i"
	make clean 1>/dev/null 2> /dev/null
	make max.out 1>/dev/null 2> /dev/null
	o=$(./max.out  | awk '{ print $3 }')
	echo -n $o,
done

echo "]"


threads="1 2 4 8 12 16 20 24 28 32"
echo -n "data_omp4= ["
for i in $threads
do
	export DEF="-DOMP4 -DNTHREADS=$i"
	make clean 1>/dev/null 2> /dev/null
	make max.out 1>/dev/null 2> /dev/null
	o=$(./max.out  | awk '{ print $3 }')
	echo -n $o,
done

echo "]"