#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -J task3
#SBATCH -o task3.out
#SBATCH -e task3.err
#SBATCH -c 1
#SBATCH -t 0-00:20:00

g++ task3.cpp matmul.cpp -Wall -O3 -std=c++17 -o task3
./task3
