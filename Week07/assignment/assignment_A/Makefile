CC=gcc

assignment_A : first_rw_problem.o
	gcc -pthread -o assignment_A first_rw_problem.o

first_rw_problem.o : first_rw_problem.c
	gcc -c -o first_rw_problem.o first_rw_problem.c

clean :
	rm assignment_A
	rm first_rw_problem.o