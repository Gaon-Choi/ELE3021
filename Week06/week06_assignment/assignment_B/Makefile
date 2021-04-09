CC = gcc

all: parent.o child.o
	gcc -o parent parent.o
	gcc -o child child.o

parent.o: parent_process.c
	gcc -c -o parent.o parent_process.c
	
child.o: child_process.c
	gcc -c -o child.o child_process.c



clean:
	rm *.o
	rm parent
	rm child