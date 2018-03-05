#!/bin/bash

module load intel

./run 5000 5000 5000 8 | tee result/8_2.result
