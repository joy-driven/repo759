#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -J task4
#SBATCH -o task4.out
#SBATCH -e task4.err
#SBATCH -c 8
#SBATCH -t 0-00:45:00

g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

N=1000
T_END=100

# each point is run 3 times and the times are averaged
run_avg() {
    for r in 1 2 3; do
        OMP_SCHEDULE=$1 ./task3 $N $T_END $2 | sed 's/[^0-9.]//g'
    done | awk '{s += $1} END {print s / NR}'
}

# lines "policy num_threads time_ms"
rm -f task4_times.txt
for policy in static dynamic guided; do
    for t in $(seq 1 8); do
        echo "$policy $t $(run_avg $policy $t)" >> task4_times.txt
    done
done
cat task4_times.txt
