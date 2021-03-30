CC = gcc

all: reader_Aprocess.o writer_Bprocess.o
	gcc -o reader_Aprocess reader_Aprocess.o
	gcc -o writer_Bprocess writer_Bprocess.o

reader_Aprocess.o: reader_Aprocess.c
	gcc -c -o reader_Aprocess.o reader_Aprocess.c
writer_Bprocess.o: writer_Bprocess.c
	gcc -c -o writer_Bprocess.o writer_Bprocess.c



clean:
	rm *.o
	rm reader_Aprocess
	rm writer_Bprocess