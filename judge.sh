#!/bin/bash

if [ $? -eq 0 ];
then
    ls | grep results.txt &>/dev/null
    if [ $? -eq 0 ];
    then
        rm results.txt
    fi
    
    total=7
    wrong=0
    for i in $( seq 1 $total )
    do
        echo "running test number $i"
        make >> /dev/null
        ./utaxi.out tests/locations.csv < ./tests/$i/$i.in > judge.out
        cmp -s judge.out ./tests/$i/$i.out
        if [ $? -eq 1 ];
        then
            wrong=$((wrong+1))
            echo "test number $i: " >> results.txt
            diff judge.out ./tests/$i/$i.out >> results.txt
            echo "________________________________" >> results.txt
        fi
    done
    echo "$total tests, $(expr $total - $wrong) right, $wrong wrong"
fi
rm judge.out
rm utaxi.out
