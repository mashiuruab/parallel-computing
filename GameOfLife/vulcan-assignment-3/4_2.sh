#!/bin/bash

module load intel

./run 5000 5000 5000 4 | tee result/4_2.result
