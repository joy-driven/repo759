#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -J task1
#SBATCH -o task1.out
#SBATCH -e task1.err
#SBATCH -c 20
#SBATCH -t 0-00:30:00

g++ task1.cpp matmul.cpp -Wall -O3 -std=c++17 -o task1 -fopenmp

# n = 1024, t = 1..20; each t is run 3 times and the times are averaged
# one line "t time_ms" per thread count
rm -f task1_times.txt
for t in $(seq 1 20); do
    avg=$(for r in 1 2 3; do ./task1 1024 $t | tail -n 1; done | awk '{s += $1} END {print s / NR}')
    echo "$t $avg" >> task1_times.txt
done
./task1 1024 20
cat task1_times.txt
