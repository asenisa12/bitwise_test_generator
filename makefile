all: generator clean

generate.o: headers/generate.hh headers/generate.cc
	g++ -c headers/generate.cc 

main.o: main.cc
	g++ -c main.cc 

generator: generate.o main.o
	g++ generate.o main.o -o generator 
clean:
	rm -rf *.o