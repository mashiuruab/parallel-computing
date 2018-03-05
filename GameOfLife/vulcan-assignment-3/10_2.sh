#!/bin/bash

module load intel

./run 5000 5000 5000 10 | tee result/10_2.result
