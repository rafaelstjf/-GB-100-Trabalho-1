#!/bin/bash
buffer=""
buffer+="n,m,execution time (s),tile size"
buffer+=$'\n'
use_cache=0
for n in {10..20..10} ;do
    for m in {10..20..10};do
        for t in {2..100..2};do
            START=$(date +%s.%N)
            ./main $n $m $use_cache $t
            END=$(date +%s.%N)
            printf -v DELTA "%g" $(bc <<<"$END - $START")
            buffer+="${n},${m},${DELTA},$t"
            buffer+=$'\n'
        done
    done
done
if [ $use_cache == 0 ] 
then
    rm ./saida_normal.txt
    echo "$buffer" >> saida_normal.txt
else
    rm ./saida.txt
    echo "$buffer" >> saida.txt
fi