#include "readfile.h"
#include "rendermap.h"
#include "writefile.h"
#include "commandmode.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <stddef.h>
void cleanLastRow();
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
	char name[100] = "unknown author";
	char level[100] = "unknown level desciption";
	
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
	editMode(fileName,authorName,mapLevel,rows,cols,mapArray);
    
	free(rows);
	free(cols);
	free(mapArray);
	endwin();
}
