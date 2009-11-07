FLAGS=-O2 -lgmpxx -lgmp
all:
	g++ ${FLAGS} main.cpp pollards.h pollards.cpp

run: all
	./a.out
