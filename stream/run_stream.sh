

threads="1 2 4 8 12 16 20 24 28 32"
schedules="static guided dynamic"

for s in $schedules
do
export SCHEDULE="schedule($s)"
echo -n "data_$s = ["
	for i in $threads
	do

		export OMP_NUM_THREADS=$i
		make clean 1>/dev/null 2> /dev/null
		make stream.out 1>/dev/null 2> /dev/null
		
		o=$(./stream.out | grep Copy | awk '{ print $2 }')

		echo -n $i, $o,
	done

echo "]"
done