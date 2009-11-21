FLAGS=-O2 -lgmpxx -lgmp
FILES=main.cpp pollards.h pollards.cpp trial_division.h trial_division.cpp fermat_squares.h fermat_squares.cpp

all: compile clean

compile:
	g++ ${FLAGS} ${FILES}

valgrind:
	g++ -g -O0 -lgmpxx -lgmp ${FILES}

run: all
	./a.out

submit: all
	./submit.py -f -p factoring ${FILES}

clean:
	rm *.gch
