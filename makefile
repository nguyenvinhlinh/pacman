CC=gcc
CFLAGS= -Wall -g -pg -std=c99
SOURCES= readfile.c rendermap.c writefile.c
HEADERS= readfile.h rendermap.h writefile.h
LIBS= -lncurses
wololo:
	$(CC) $(CFLAGS) -o  ProgramTester $(SOURCES) $(LIBS)

