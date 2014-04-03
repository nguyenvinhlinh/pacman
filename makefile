CC=gcc
CFLAGS=  -g -pg -std=c99
SOURCES= readfile.c rendermap.c writefile.c commandmode.c  ProgramLaucher.c
HEADERS= readfile.h rendermap.h writefile.h commandmode.h 		
OBJS = $(patsubst %.c,%.o,$(SOURCES))
LIBS= -lncurses

pacman:  $(HEADERS) $(OBJS) 
	$(CC) $(CFLAGS) -o  pacman $(SOURCES) $(LIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:	
	rm *.o 

.PHONY: cleanall
cleanall:
	rm *.o  pacman
