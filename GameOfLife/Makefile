all: run

run: openmpi_test.cpp
	g++ -g -Wall -fopenmp -o run -std=c++11 main3.cpp -DDEBUG_PRINT

clean:
	-rm run