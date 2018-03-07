all: run

run: main_omp.cpp
	icc -g -Wall -openmp -o run -std=c++11 main_omp.cpp

clean:
	-rm run