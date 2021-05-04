CC=gcc

assignment_B : dining_philosophers_problem.o
	gcc -pthread -o assignment_B dining_philosophers_problem.o

dining_philosophers_problem.o : dining_philosophers_problem.c
	gcc -c -o dining_philosophers_problem.o dining_philosophers_problem.c

clean :
	rm assignment_B
	rm dining_philosophers_problem.o