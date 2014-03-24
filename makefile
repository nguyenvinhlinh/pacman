CC=gcc
CFLAGS= -Wall -g -pg -std=c99
SOURCES= readfile.c rendermap.c writefile.c ProgramTester.c
HEADERS= readfile.h rendermap.h writefile.h
LIBS= -lncurses
ProgramTester: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o  ProgramTester $(SOURCES) $(LIBS)

