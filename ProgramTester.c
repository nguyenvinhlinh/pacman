#include "readfile.h"
#include "rendermap.h"
#include "writefile.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <stddef.h>
void cleanLastRow();
void fullCommandMode(char * fileName, char * authorName, char * mapDescription, int * rows, int * cols, char * mapArray, int * isQuit){
	int h,w;
	getmaxyx(stdscr,h,w);
	//clean the last row and move curse to the h-1,0
	move(h-1,0);
	for (int i = 0; i < w; i++) {
		addch(' ');
	}
	move(h-1,0);
	echo();
	addch(':');
//take input from user
	char buffer[100]= " ";
	for (int i = 0 ; i < 100; i++) {
		buffer[i] = getch();
		if(buffer[i] == '\n'){
			printw("%s", buffer);
			char delimeter[] = " ";
			char *token1, *token2, *token3, *token4;
			buffer[i] = ' ';
			char *cp = strdup(buffer);		
			token1 = strtok(cp, delimeter);
			token2 = strtok(NULL, delimeter);
			token3 = strtok(NULL, delimeter);
			token4 = strtok(NULL, delimeter);
					
			if(strcmp(token1, "q") == 0){
				isQuit[0] = 1;
				break;
			} else if (strcmp(token1,"r") == 0 && token2 != NULL){
				char bufferauthorName[100] = " ";
				char bufferlevel[100] = " ";
				int c = 0;
				int r = 0;
				char * pointerAuthor = &bufferauthorName[0];
				char * pointerlevel = &bufferlevel[0];
				int * pointerCols = &c;
				int * pointerRows = &r;
				char * buff = readFile(token2, pointerAuthor, pointerlevel, pointerCols, pointerRows);
				if (buff == NULL){
					getmaxyx(stdscr,h,w);
					//clean the last row and move curse to the h-1,0
					move(h-1,0);
					for (int i = 0; i < w; i++) {
						addch(' ');
					}
					move(h-1,0);
					printw("File not found!");
				} else {
					//fileName
					for (int i = 0;; i++) {
						fileName[i] = token2[i];
						if(fileName[i] == NULL)break;
					}
					//push bask to name and level variable
					for (int i = 0;i < 100 ; i++) {
						authorName[i] = pointerAuthor[i];
						if(authorName[i] == NULL)break;
					}
					//level description
					for (int i = 0;i < 100 ; i++) {
						mapDescription[i] = pointerlevel[i];
						if(mapDescription[i] == NULL)break;
					}
					//rows and cols
					rows[0] = pointerRows[0];
					cols[0] = pointerCols[0];
					for (int i = 0; i < cols[0] * rows[0]; i++) {
						mapArray[i] = buff[i];
						if(i == rows[0] * cols[0] -1){
							mapArray[i + 1] = NULL;
						}
					}		
					clear();
					move(0,0);
					printw("File name: %s\n", fileName);
					printw("AuthorName: %s\n", authorName);
					printw("Map level: %s\n", mapDescription);
					printw("Number of Rows: %d\n", rows[0]);
					printw("Number of Cols: %d\n", cols[0]);
					renderMap(mapArray, rows[0], cols[0]);				
				}
				break;
			} else if (strcmp(token1, "w") == 0 && token2 != NULL){
				for (int i = 0;; i++) {
					fileName[i] = token2[i];
					if(fileName[i] == NULL)break;
				}
				writeFile(fileName , authorName, mapDescription, cols[0], rows[0], mapArray);
				clear();
				move(0,0);
				printw("File name: %s\n", fileName);
				printw("AuthorName: %s\n", authorName);
				printw("Map level: %s\n", mapDescription);
				printw("Number of Rows: %d\n", rows[0]);
				printw("Number of Cols: %d\n", cols[0]);
				renderMap(mapArray, rows[0], cols[0]);
				cleanLastRow();
				move(h-1,0);
				printw("Printed to file named %s", fileName);
				break;
			} else if (strcmp(token1, "wq") == 0){
				writeFile(fileName, authorName, mapDescription, cols[0], rows[0], mapArray);
				getmaxyx(stdscr,h,w);
				move(h-1,0);
				for (int i = 0 ; i < w; i++) {
					addch(' ');
				}
				move(h-1,0);
				printw("Printed to file named %s", fileName);
						
				isQuit[0] = 1;
				break;
			} else if (strcmp(token1, "w")== 0 && token2 == NULL){
				writeFile(fileName , authorName, mapDescription, cols[0], rows[0], mapArray);
				getmaxyx(stdscr,h,w);
				move(h-1,0);
				printw("Printed to file named %s", fileName);
				break;
			}else if(strcmp(token1, "n") == 0 && token2 != NULL && token3 != NULL && token4 != NULL){
				while (1) {
					fileName[i] = token2[i];
					if(fileName[i] == NULL)break;
				}
				rows[0] = atoi(token3);
				cols[0] = atoi(token4);
				if(atoi(token3) >= 30 && atoi(token4) >= 65){
					cleanLastRow();
					move(0,0);
					printw("Invalid rows and cols, rows <= 30, cols <= 65");
					break;
				}
				for (int i = 0; i < rows[0] * cols[0]; i++) {
					mapArray[i] = ' ';
				}
				isQuit[0] = 1;
				break;
			}else {
				getmaxyx(stdscr,h,w);
				move(h-1,0);
				printw("Invalid command!");
				break;
			}
		} else if (buffer[i] == 27){
			getmaxyx(stdscr,h,w);
			move(h-1,0);
			for (int i = 0 ; i < w; i++) {
				addch(' ');
			}
			move(0,0);
			break;									  
		}
	}
}
void editMode(char * fileName, char * authorName, char * mapDescription, int * rows, int * cols, char * mapArray){
	int quit = 0;
	int * quitP = &quit;
	while(quit == 0){
		noecho();
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
			(void)fullCommandMode(fileName, authorName,mapDescription, rows, cols, mapArray, quitP);
		}
		if(getcury(stdscr) > 4 && getcury(stdscr) <= 4 + rows[0] && getcurx(stdscr) < cols[0]){
			int currentRow;
			int currentCol;
			getyx(stdscr, currentRow, currentCol);
			currentRow = currentRow - 5;
			//	printw("rows: %d, col: %d \n",currentRow, currentCol );
			if (c == 'q' || c == 'Q') {
				mapArray[cols[0] * currentRow + currentCol] = 'q';
				addch(ACS_ULCORNER);
			} else if (c == 'w' || c == 'x') {
				mapArray[cols[0] * currentRow + currentCol] = 'w';
				addch(ACS_HLINE);
			} else if (c == 'e' || c == 'E') {
				mapArray[cols[0] * currentRow + currentCol] = 'e';
				addch(ACS_URCORNER);
			} else if (c == 'a' || c == 'd') {
				mapArray[cols[0] * currentRow + currentCol] = 'a';
				addch(ACS_VLINE);
			} else if (c == 'z' || c == 'Z') {
				mapArray[cols[0] * currentRow + currentCol] = 'z';
				addch(ACS_LLCORNER);
			} else if (c == 'c' || c == 'C') {
				mapArray[cols[0] * currentRow + currentCol] = 'c';
				addch(ACS_LRCORNER);
			} else if (c == 'W'){
				mapArray[cols[0] * currentRow + currentCol] = 'W';
				addch(ACS_TTEE);
			} else if (c == 'D'){
				mapArray[cols[0] * currentRow + currentCol] = 'D';
				addch(ACS_RTEE);
			} else if (c == 'X'){
				mapArray[cols[0] * currentRow + currentCol] = 'X';
				addch(ACS_BTEE);
			} else if(c == 'A'){
				mapArray[cols[0] * currentRow + currentCol] = 'A';
				addch(ACS_LTEE);
			} else if (c == 's') {
				mapArray[cols[0] * currentRow + currentCol] = 's';
				addch(ACS_BULLET);
			} else if (c == 'S') {
				mapArray[cols[0] * currentRow + currentCol] = 'S';
				addch(ACS_DIAMOND);
			} else if (c == 'g' || c == 'G') {
				mapArray[cols[0] * currentRow + currentCol] = 'g';
				addch(ACS_CKBOARD);
			} else if (c == 'p' || c == 'P') {
				mapArray[cols[0] * currentRow + currentCol] = 'p';
				addch(ACS_PI);
			} else if (c == 'f' || c == 'F') {
				mapArray[cols[0] * currentRow + currentCol] = 'f';
				addch(ACS_STERLING);
			} else if (c == ' ') {
				mapArray[cols[0] * currentRow + currentCol] = ' ';
				addch(' ');
			}
		}		
	}
}
void cleanLastRow(){
	int h,w;
	getmaxyx(stdscr,h,w);
	move(h-1,0);
	for (int i = 0; i < w; i++) {
		addch(' ');
	}
	move(h-1,0);
	
}
void  main(){
	//init curses context
	(void) initscr();
	keypad(stdscr, TRUE);
	(void) cbreak();
	(void) noecho();
	//finished initing curses context
	char file[100] = "demofile.pac";
	char name[100] = "unknown";
	char level[100] = "unknown";
	
	char * fileName = &file[0]; 
	char * authorName = &name[0];
	char * mapLevel = &level[0];
	int * rows = malloc(sizeof(int)* 1);
	int * cols = malloc(sizeof(int)*1);	
	char * mapArray = malloc(sizeof(char)* 2000);
	rows[0] = 0;
	cols[0] = 0;
	int quit = 0;
	int *  isQuit = &quit;
	int h,w;
	getmaxyx(stdscr,h,w);
	printw("%d %d", h,w);
	getch();
	editMode(fileName,authorName,mapLevel,rows,cols,mapArray);
    
	free(rows);
	free(cols);
	free(mapArray);
	endwin();
}
