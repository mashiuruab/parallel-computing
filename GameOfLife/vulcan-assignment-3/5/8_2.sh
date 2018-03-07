#!/bin/bash

module load intel

./run 8 2 10 1 >> result/8_2.result
./run 8 2 10 2 >> result/8_2.result
./run 8 2 10 4 >> result/8_2.result
./run 8 2 10 8 >> result/8_2.result
./run 8 2 10 10 >> result/8_2.result
./run 8 2 10 16 >> result/8_2.result
./run 8 2 10 20 >> result/8_2.result
