.PHONY: all clean
# Object declarations
FLAGS = -std=c99 -Wall -Wextra -Wvla
CC = gcc
SKIP_LINKAGE = -c

########################################################
all: sudukusolver genericdfs.a

sudukusolver: sudukusolver.o genericdfs.o sudukutree.o
	$(CC) -g $(FLAGS) sudukusolver.o genericdfs.o sudukutree.o -o  sudukusolver -lm

sudukusolver.o: sudukusolver.c sudukutree.h
	$(CC) -g $(SKIP_LINKAGE) $(FLAGS) sudukusolver.c
	
genericdfs.o: genericdfs.c
	$(CC) -g $(SKIP_LINKAGE) $(FLAGS) genericdfs.c

genericdfs.a: genericdfs.o
	ar rcs genericdfs.a genericdfs.o
	
sudukutree.o: sudukutree.c sudukutree.h
	$(CC) -g $(SKIP_LINKAGE) $(FLAGS) sudukutree.c

clean:
	rm -f *.o sudukusolver genericdfs.a
