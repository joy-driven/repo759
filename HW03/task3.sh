#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -J task3
#SBATCH -o task3.out
#SBATCH -e task3.err
#SBATCH -c 20
#SBATCH -t 0-00:30:00

g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

# each point is run 3 times and the times are averaged
run_avg() {
    for r in 1 2 3; do ./task3 1000000 $1 $2 | tail -n 1; done | awk '{s += $1} END {print s / NR}'
}

# part 1: n = 10^6, t = 8, ts = 2^1 ... 2^10, lines "ts time_ms"
rm -f task3_ts_times.txt
for p in $(seq 1 10); do
    ts=$((2 ** p))
    echo "$ts $(run_avg 8 $ts)" >> task3_ts_times.txt
done

# best ts = the one with the smallest time
best_ts=$(sort -g -k2 task3_ts_times.txt | head -n 1 | awk '{print $1}')
echo "best ts = $best_ts"

# part 2: n = 10^6, t = 1 ... 20 with the best ts, lines "t time_ms"
rm -f task3_t_times.txt
for t in $(seq 1 20); do
    echo "$t $(run_avg $t $best_ts)" >> task3_t_times.txt
done
echo "$best_ts" > task3_best_ts.txt

./task3 1000000 8 $best_ts
cat task3_ts_times.txt
cat task3_t_times.txt
