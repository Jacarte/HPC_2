
export CFLAGS=""
make clean 
make 

INPUT="3 0.05 100 100 10 10 10 10 200 15 30 10 10 100000 100 100 1 0"

p1=$(./nbody.out <<< $INPUT)


export CFLAGS="-DREDUCED"
make clean 
make 

p2=$(./nbody.out <<< $INPUT)

if [[ $p1 != $p2 ]]; then
	echo "The result should be the same"
	exit 1
fi



export CC=gcc-9
export CFLAGS="-DREDUCED -fopenmp"
make clean 
make 

p3=$(./nbody.out <<< $INPUT)

if [[ $p1 != $p3 ]]; then
	echo "The result should be the same"
	exit 1
fi