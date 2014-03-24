#include "readfile.h"
#include "rendermap.h"
#include "writefile.h"
#include "editcell.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
int main(){

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
	rows[0] = 0;
	cols[0] = 0;
	//Load map
	char * mapArray =  readFile(fileName, authorName, mapLevel, cols, rows);
	
//	printf("Author name: %s", name);
//	printf("Map description: %s", level);
//	printf("Number of rows: %d\n", rows[0]);
//	printf("Number of cols: %d\n", cols[0]);

	printw("Author name: %s", name);
	printw("Map description: %s", level);
	printw("Number of rows: %d\n", rows[0]);
	printw("Number of cols: %d\n", cols[0]);
	//try to render map
/*	for (int i = 0; i < rows[0] * cols[0]; i++) {
		printw("%c ", mapArray[i]);
		}*/
	renderMap(mapArray, rows[0], cols[0]);
	for(;;){
		int c = getch();
		if (c == KEY_RIGHT) {
			move(getcury(stdscr), getcurx(stdscr) + 1);
		} else if (c == KEY_LEFT) {
			move(getcury(stdscr), getcurx(stdscr) - 1);
		} else if (c == KEY_UP) {
			move(getcury(stdscr) - 1, getcurx(stdscr));
		} else if (c == KEY_DOWN) {
			move(getcury(stdscr) + 1, getcurx(stdscr));
		} else if (c == ':') {
			break;
		}
//if current position of curse in in range(available cols and rows, allow editing)
		if(getcury(stdscr) >= 4 && getcury(stdscr) < 4 + rows[0] && getcurx(stdscr) < cols[0] ){
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
	return 0;
}


