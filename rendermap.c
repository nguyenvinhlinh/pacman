#include <ncurses.h>
#include "rendermap.h"
void renderMap(char * mapArray, int rows, int cols){
//	(void) initscr();
//	keypad(stdscr, TRUE);
//	(void) cbreak();
//	(void) noecho();
	int i,j;
	for (i = 0; i < rows * cols; i++) {
		printf("%c ", mapArray[i]);
	}
	printf("\n");
	/*for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
		   printf("%c ", mapArray[cols * i + j]);
		}
		}*/
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
		printw("\n");
	}
}
