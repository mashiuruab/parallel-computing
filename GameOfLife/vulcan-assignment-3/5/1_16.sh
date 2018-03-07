#!/bin/bash

module load intel

./run 1 16 10 1 >> result/1_16.result
./run 1 16 10 2 >> result/1_16.result
./run 1 16 10 4 >> result/1_16.result
./run 1 16 10 8 >> result/1_16.result
./run 1 16 10 10 >> result/1_16.result
./run 1 16 10 16 >> result/1_16.result
./run 1 16 10 20 >> result/1_16.result

