FLAGS=-O2 -lgmpxx -lgmp
all:
	g++ ${FLAGS} main.cpp

run: all
	./a.out
