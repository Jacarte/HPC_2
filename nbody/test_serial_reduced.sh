
export CFLAGS=""
make clean 1>/dev/null 2> /dev/null
make 1>/dev/null 2> /dev/null

p1=$(./nbody.out <<< "3 0.05 100 100 10 10 10 10 200 15 30 10 10 100000 100 100 1 0")


export CFLAGS="-DREDUCED"
make clean 1>/dev/null 2> /dev/null
make 1>/dev/null 2> /dev/null

p2=$(./nbody.out <<< "3 0.05 100 100 10 10 10 10 200 15 30 10 10 100000 100 100 1 0")

if [[ $p1 != $p2 ]]; then
	echo "The result should be the same"
fi