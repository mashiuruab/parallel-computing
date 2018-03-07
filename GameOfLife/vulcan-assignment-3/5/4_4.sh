#!/bin/bash

module load intel

./run 4 4 10 1 >> result/4_4.result
./run 4 4 10 2 >> result/4_4.result
./run 4 4 10 4 >> result/4_4.result
./run 4 4 10 8 >> result/4_4.result
./run 4 4 10 10 >> result/4_4.result
./run 4 4 10 16 >> result/4_4.result
./run 4 4 10 20 >> result/4_4.result
