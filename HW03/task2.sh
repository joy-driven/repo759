#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -J task2
#SBATCH -o task2.out
#SBATCH -e task2.err
#SBATCH -c 20
#SBATCH -t 0-00:30:00

g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp

# n = 1024, t = 1..20; each t is run 3 times and the times are averaged
# one line "t time_ms" per thread count
rm -f task2_times.txt
for t in $(seq 1 20); do
    avg=$(for r in 1 2 3; do ./task2 1024 $t | tail -n 1; done | awk '{s += $1} END {print s / NR}')
    echo "$t $avg" >> task2_times.txt
done
./task2 1024 20
cat task2_times.txt
