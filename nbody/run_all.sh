

N="500 1000 2000"

# SERIAL
for i in $N
do
	export CFLAGS=-DMEASURE_TIME
	make clean 1>/dev/null 2> /dev/null
	make 1>/dev/null 2> /dev/null
	
	./nbody.out <<< "$i 0.05 100"
done