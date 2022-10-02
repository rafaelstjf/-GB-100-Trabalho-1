#!/bin/bash
buffer=""
buffer+="n,m,execution time (s),tile size"
buffer+=$'\n'
use_cache=1

for (( n = 64; n <= 128; n=2*n ));do
    for (( m = 16384; m <= 1048576; m=2*m ));do
        for (( t = 128; t <= 16384; t=2*t));do
            time_exec=$(\time -f '%e' ./main $n $m $use_cache $t 2>&1)
            echo "Time: $time_exec"
            buffer+="${n},${m},${time_exec},$t"
            buffer+=$'\n'
        done
    done
done
if [ $use_cache == 0 ] 
then
    rm ./saida_normal.txt
    echo "$buffer" >> saida_normal.csv
else
    rm ./saida.txt
    echo "$buffer" >> saida.csv
fi