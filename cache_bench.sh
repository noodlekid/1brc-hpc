#!/bin/bash

taskset -c 3 ./target/1brc test/benchmark_set/measurements1B.txt

perf stat -e L1-dcache-loads:u,LLC-loads:u,LLC-load-misses:u taskset -c 3 ./target/1brc test/benchmark_set/measurements1B.txt

