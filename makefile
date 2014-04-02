CC=gcc
CFLAGS=  -g -pg -std=c99
SOURCES= readfile.c rendermap.c writefile.c commandmode.c  ProgramTester.c
HEADERS= readfile.h rendermap.h writefile.h commandmode.h 
LIBS= -lncurses
ProgramTester: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o  ProgramTester $(SOURCES) $(LIBS)

