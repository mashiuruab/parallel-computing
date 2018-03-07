#!/bin/bash

module load intel

./run 16 1 10 1 >> result/16_1.result
./run 16 1 10 2 >> result/16_1.result
./run 16 1 10 4 >> result/16_1.result
./run 16 1 10 8 >> result/16_1.result
./run 16 1 10 10 >> result/16_1.result
./run 16 1 10 16 >> result/16_1.result
./run 16 1 10 20 >> result/16_1.result

