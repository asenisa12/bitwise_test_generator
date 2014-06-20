all: generator clean

generate.o: headers/generate.hh headers/generate.cc
	g++ -c headers/generate.cc

main.o: main.cc
	g++ -c main.cc -std=c++11

generator: generate.o main.o
	g++ generate.o main.o  

clean:
	rm -rf *.o