#variable for compiler
CC=gcc
#variable for Flags
CFLAGS = -Wall -ansi -pedantic
#Make Code
all:	GameOfLife.o
	$(CC) GameOfLife.o -o life 
GameOfLife.o:	Driver.c GameBoard.h GameOfLife.h
	$(CC) $(CFLAGS) -c Driver.c
