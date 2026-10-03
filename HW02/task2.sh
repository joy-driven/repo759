#!/usr/bin/env bash
#SBATCH -p instruction
#SBATCH -J task2
#SBATCH -o task2.out
#SBATCH -e task2.err
#SBATCH -c 1
#SBATCH -t 0-00:10:00

g++ convolution.cpp task2.cpp -Wall -O3 -std=c++17 -o task2
./task2 1024 3
