# makefile

program: lab2.o
	g++ -std=c++11 lab2.o -o main

lab2.o: lab2.cpp
	g++ -std=c++11 -c lab2.cpp

clean:
	rm *.o