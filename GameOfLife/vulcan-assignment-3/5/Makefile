all: run

run: main_omp_nano.cpp
	icc -g -Wall -openmp -o run -std=c++11 main_omp_nano.cpp

clean:
	-rm run
