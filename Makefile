ifeq ($(DEBUG),true)
	CC = gcc -g
else
	CC = gcc
endif

all: fileStat.o
	$(CC) -o fileStat fileStat.o

fileStat.o: fileStat.c
	$(CC) -c fileStat.c

run:
	./fileStat
