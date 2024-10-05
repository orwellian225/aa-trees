#!/bin/sh

for n in {0..10000..100}
do
    echo "n = " $n
    for trial in {1..10}
    do
        ./build/random-insert $n  $((n / 3)) >> data/random_construction_data.csv
        ./build/descending-insert $n  $((n / 3)) >> data/descending_construction_data.csv
    done
done
