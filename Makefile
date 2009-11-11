FLAGS=-O2 -lgmpxx -lgmp
all:
	g++ ${FLAGS} main.cpp pollards.h pollards.cpp trial_division.h trial_division.cpp

run: all
	./a.out

submit: all
	./submit.py -f -p factoring main.cpp pollards.h pollards.cpp trial_division.h trial_division.cpp

