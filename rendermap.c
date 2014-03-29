#include <ncurses.h>
#include "rendermap.h"
void renderMap(char * mapArray, int rows, int cols){
//	(void) initscr();
//	keypad(stdscr, TRUE);
//	(void) cbreak();
//	(void) noecho();
	int i,j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			char c = mapArray[cols * i + j];
			//	printf("%c ", c);
			if (c == 'q' || c == 'Q') {
				addch(ACS_ULCORNER);
			} else if (c == 'w' || c == 'x') {
				addch(ACS_HLINE);
			} else if (c == 'e' || c == 'E') {
				addch(ACS_URCORNER);
			} else if (c == 'a' || c == 'd') {
				addch(ACS_VLINE);
			} else if (c == 'z' || c == 'Z') {
				addch(ACS_LLCORNER);
			} else if (c == 'c' || c == 'C') {
				addch(ACS_LRCORNER);
			} else if (c == 'W'){
				addch(ACS_TTEE);
			} else if (c == 'D'){
				addch(ACS_RTEE);
			} else if (c == 'X'){
				addch(ACS_BTEE);
			} else if(c == 'A'){
				addch(ACS_LTEE);
			} else if (c == 's') {
				addch(ACS_BULLET);
			} else if (c == 'S') {
				addch(ACS_DIAMOND);
			} else if (c == 'g' || c == 'G') {
				addch(ACS_CKBOARD);
			} else if (c == 'p' || c == 'P') {
				addch(ACS_PI);
			} else if (c == 'f' || c == 'F') {
				addch(ACS_STERLING);
			} else if (c == ' ') {
				addch(' ');
			}
		}
		printw("\n");
	}
}
