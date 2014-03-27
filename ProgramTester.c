#include "readfile.h"
#include "rendermap.h"
#include "writefile.h"
#include "editcell.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <stddef.h>

//prior to launch command mode, user type ':'
void lauchCommandMode(char * fileName, char * authorName, char * mapLevel, int * rows, int * cols, char * mapArray, int * isQuit ){
	const char delimeter[] = " ";
	char *token1, *token2, *token3, *token4;
	char s[100] = "";
	for (;;) {
		wrefresh(stdscr);
		getstr(s);
		//strdup() return a pointer of a string
		char *cp = strdup(s);		
		token1 = strtok(cp, delimeter);
		token2 = strtok(NULL, delimeter);
		token3 = strtok(NULL, delimeter);
		token4 = strtok(NULL, delimeter);
		if (strcmp(token1, "q") == 0) {
			printw("Quit\n");
		} else if (strcmp(token1, "w") == 0) {
			//write to file
			//if the file name is null, cannot be active
			printw("Write to current file\n");
		} else if (strcmp(token1, "wq") == 0) {
			//write and quit
			//if the file name is null,it will quit
			printw("Write to current file and quit\n");
			break;
		} else if (strcmp(token1, "r") == 0 && token2 != NULL) {
			//read the file name token2
			printw("Read from file\n");
		} else if (strcmp(token1, "n") == 0 && token2 != NULL && token3 != NULL && token4 != NULL) {
			//create a new level with token3 rows and token4 columns
			//if value of token 2 and 3 is not an integer and out of
			//valid range, report error!
			printw("Make new file\n");
		} else {
			printw("Invalid command!\n");
		}
	}
}


int lauchSemiCommandMode(char * fileName, char * authorName, char * mapLevel, int * rows, int * cols, char * mapArray, int * isQuit ){
	int isQuitFromFunction = 0;
	while(1){
		if(isQuit[0] == 1) break;
		if(isQuitFromFunction == 1) break;
		printw("In semi-cmd");
		int c = getch();
		char buffer[200]; //this buffer will take all argument
		if(c == ':'){
			int h,w;
			getmaxyx(stdscr,h,w);
			move(h-1,0);
			addch(':');
			for (int i = 0; i < 200; i++) {
				echo();
				buffer[i] = getch();
				//if the last input is enter, analyze whole input and
				//execute
				if(buffer[i] == '\n'){
					printw("Enter");
					//from now, this function will analyze the whole
					//buffer to choose suitable function include read
					//file, new file, and quit
					char delimeter[] = " ";
					char *token1, *token2, *token3, *token4;
				   	buffer[i] = ' ';
					char *cp = strdup(buffer);		
					token1 = strtok(cp, delimeter);
					token2 = strtok(NULL, delimeter);
					token3 = strtok(NULL, delimeter);
					token4 = strtok(NULL, delimeter);
					if (strcmp(token1, "q") == 0) {
						isQuit[0] = 1;
						printw("Quit\n");
						break;
					} else if (strcmp(token1, "r") == 0 && token2 != NULL) {
						//read the file name token2
						move(0,0);
						fileName = token2;
						char * buff  = readFile(fileName,authorName, mapLevel, cols, rows);
						for (int i = 0; i < rows[0] * cols[0]; i++) {
							mapArray[i] = buff[i];
						}
						if(cols[0] != 0){
							//map is loaded, no error
							isQuitFromFunction = 1;
						}
						
						move(0,0);
						printw("File not found!");
						break;
					} else if (strcmp(token1, "n") == 0 && token2 != NULL && token3 != NULL && token4 != NULL) {
						//create a new level with token3 rows and token4 columns
						//if value of token 2 and 3 is not an integer and out of
						//valid range, report error!
						
						printw("Make new file\n");
						isQuitFromFunction = 1;
					} else {
						printw("Invalid command!\n");
						break;
					}
				}
				//if the last input is ESC, quit current loop
				if(buffer[i] == 27){
					printw("ESC");
					break;
				}
				if(buffer[i] == 263 && i >= 1){
					i = i - 2;
				}	
			}
		}
		//now, we will use a loop to take every single input char
		

	}
}
void  main(){
	//init curses context
	(void) initscr();
	keypad(stdscr, TRUE);
	(void) cbreak();
	(void) noecho();
	//finished initing curses context
	char file[] = "level1.pac";
	char name[100] = "unknown";
	char level[100] = "unknown";
	
	char * fileName = &file[0]; 
	char * authorName = &name[0];
	char * mapLevel = &level[0];
	int * rows = malloc(sizeof(int)* 1);
	int * cols = malloc(sizeof(int)*1);
	
	char * mapArray = malloc(sizeof(char)* 500);
	rows[0] = 0;
	cols[0] = 0;
	int quit = 0;
	int *  isQuit = &quit;
	char a = '1';
	char * beta = &a;
	lauchSemiCommandMode(fileName,authorName,mapLevel,rows,cols,mapArray,isQuit);
	
	printw("File name: %s", fileName);
	printw("AuthorName: %s", authorName);
	printw("Map level: %s", mapLevel);
	printw("Rows: %d", rows[0]);
	printw("Cols: %d", cols[0]);
	printw("MapArray: %s", mapArray);

	getch();
	free(rows);
	free(cols);
	free(mapArray);
	endwin();
	
}

