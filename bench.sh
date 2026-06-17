#!/bin/bash

make

# warm up
for i in {1..3}
do
    taskset -c 3 ./target/1brc ./test/benchmark_set/measurements100M.txt > /dev/null 2>&1
done

perf stat -r 10 taskset -c 3 ./target/1brc ./test/benchmark_set/measurements100M.txt > /dev/null
