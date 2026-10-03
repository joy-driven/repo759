#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -J task1
#SBATCH -o task1.out
#SBATCH -e task1.err
#SBATCH -c 1
#SBATCH --mem=20G
#SBATCH -t 0-00:30:00

g++ scan.cpp task1.cpp -Wall -O3 -std=c++17 -o task1

# scaling analysis: n = 2^10 ... 2^30, one line "n time_ms" per run
rm -f task1_times.txt
for p in $(seq 10 30); do
    n=$((2 ** p))
    t=$(./task1 $n | head -n 1)
    echo "$n $t" >> task1_times.txt
done
cat task1_times.txt
