#include "readfile.h"
#include "rendermap.h"
#include "writefile.h"
#include "editcell.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <stddef.h>
int lauchSemiCommandMode(char * fileName, char * authorName, char * mapLevel, int * rows, int * cols, char * mapArray, int * isQuit ){
	int isQuitFromFunction = 0;
	while(1){
		if(isQuit[0] == 1) break;
		if(isQuitFromFunction == 1) break;
		int c = getch();
		char buffer[200]; //this buffer will take all argument
		if(c == ':'){
			clear();
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
	int h,w;	
	lauchSemiCommandMode(fileName,authorName,mapLevel,rows,cols,mapArray,isQuit);
	clear();
	printw("File name: %s\n", fileName);
	printw("AuthorName: %s\n", authorName);
	printw("Map level: %s\n", mapLevel);
	printw("Number of Rows: %d\n", rows[0]);
	printw("Number of Cols: %d\n", cols[0]);
	renderMap(mapArray, rows[0], cols[0]);  
	noecho();
	
	//from Here, it will be a part of full command mode
	while(quit == 0){
		int c = getch();
		if (c == KEY_RIGHT) {
			move(getcury(stdscr), getcurx(stdscr) + 1);
		} else if (c == KEY_LEFT) {
			move(getcury(stdscr), getcurx(stdscr) - 1);
		} else if (c == KEY_UP) {
			move(getcury(stdscr) - 1, getcurx(stdscr));
		} else if (c == KEY_DOWN) {
			move(getcury(stdscr) + 1, getcurx(stdscr));
		}else if (c == ':') {
			getmaxyx(stdscr,h,w);
			move(h-1,0);
			echo();
			addch(':');
//take input from user
			char buffer[100];
			for (int i = 0 ; i < 100; i++) {
				buffer[i] = getch();
				if(buffer[i] == '\n'){
					char delimeter[] = " ";
					char *token1, *token2, *token3, *token4;
				   	buffer[i] = ' ';
					char *cp = strdup(buffer);		
					token1 = strtok(cp, delimeter);
					token2 = strtok(NULL, delimeter);
					token3 = strtok(NULL, delimeter);
					token4 = strtok(NULL, delimeter);
					
					if(strcmp(token1, "q") == 0){
						quit = 1;
						break;
					} else if (strcmp(token1,"r") == 0 && token2 != NULL){
						char * buff = readFile(token2, authorName, mapLevel, cols, rows);
					   
						if (buff == NULL){
							printw("File not found!");
						} else {
							for (int i = 0; i < cols[0] * rows[0]; i++) {
								mapArray[i] = buff[i];
							}
							fileName = token2;
							clear();
							move(0,0);
						 	printw("File name: %s\n", fileName);
							printw("AuthorName: %s\n", authorName);
							printw("Map level: %s\n", mapLevel);
							printw("Number of Rows: %d\n", rows[0]);
							printw("Number of Cols: %d\n", cols[0]);
							renderMap(mapArray, rows[0], cols[0]);
							
						}
						break;
					} else if (strcmp(token1, "w") == 0 && token2 != NULL){
						fileName = token2;
						writeFile(fileName , authorName, mapLevel, cols[0], rows[0], mapArray);
						getmaxyx(stdscr,h,w);
						move(h-1,0);
						printw("Printed to file named %s", fileName);
						break;
					} else if (strcmp(token1, "wq") == 0){
						writeFile(fileName, authorName, mapLevel, cols[0], rows[0], mapArray);
						getmaxyx(stdscr,h,w);
						move(h-1,0);
						printw("Printed to file named %s", fileName);
						quit = 1;
						break;
					} else if (strcmp(token1, "w")== 0 && token2 == NULL){
						writeFile(fileName , authorName, mapLevel, cols[0], rows[0], mapArray);
						move(0,0);
						printw("Printed to file named %s", fileName);
						break;
					}
				}
			}
		}
		if(getcury(stdscr) > 4 && getcury(stdscr) <= 4 + rows[0] && getcurx(stdscr) < cols[0]){
			if (c == 'q' || c == 'Q') {
				addch(ACS_ULCORNER);
			} else if (c == 'w' || c == 'x') {
				addch(ACS_HLINE);
			} else if (c == 'e' || c == 'E') {
				addch(ACS_URCORNER);
			} else if (c == 'a' || c == 'd') {
				addch(ACS_VLINE);
			} else if (c == 's') {
				addch(ACS_BULLET);
			} else if (c == 'S') {
				addch(ACS_BLOCK);
			} else if (c == 'z' || c == 'Z') {
				addch(ACS_LLCORNER);
			} else if (c == 'c' || c == 'C') {
				addch(ACS_LRCORNER);
			} else if (c == 'g' || c == 'G') {
				addch('G');
			} else if (c == 'p' || c == 'P') {
				addch('P');
			} else if (c == 'f' || c == 'F') {
				addch('F');
			} else if (c == ' ') {
				addch(' ');				
			}
		}		
	}
	free(rows);
	free(cols);
	free(mapArray);
	endwin();
}

