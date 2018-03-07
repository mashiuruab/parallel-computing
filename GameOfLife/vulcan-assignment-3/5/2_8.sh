#!/bin/bash

module load intel

./run 2 8 10 1 >> result/2_8.result
./run 2 8 10 2 >> result/2_8.result
./run 2 8 10 4 >> result/2_8.result
./run 2 8 10 8 >> result/2_8.result
./run 2 8 10 10 >> result/2_8.result
./run 2 8 10 16 >> result/2_8.result
./run 2 8 10 20 >> result/2_8.result
