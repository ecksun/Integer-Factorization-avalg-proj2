FLAGS=-O2 -lgmpxx -lgmp
all: compile clean

compile:
	g++ ${FLAGS} main.cpp pollards.h pollards.cpp trial_division.h trial_division.cpp fermat_squares.h fermat_squares.cpp

run: all
	./a.out

submit: all
	./submit.py -f -p factoring main.cpp pollards.h pollards.cpp trial_division.h trial_division.cpp 

clean:
	rm *.gch
