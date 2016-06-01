#!/bin/bash

go(){
	tput clear
	resize -s 24 80 > /dev/null
	printf "   Bye  :-)\n"
	echo 
	exit 0
}

trap "go" 1 2 3 15
arg=0
resize -s 37 80 > /dev/null
gcc sinGraphic.c -lm -o sinGraphic >/dev/null
tput clear
while true
do
	echo $arg
	./sinGraphic $arg
	arg=$[$arg+1]
	tput cup 0 0
done
