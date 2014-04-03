#include "commandmode.h"
#include "readfile.h"
#include "rendermap.h"
#include "writefile.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <stddef.h>
void cleanLastRow();
char *strdup(const char *str);
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
						if(fileName[i] == '\0')break;
					}
					//push bask to name and level variable
					for (int i = 0;i < 100 ; i++) {
						authorName[i] = pointerAuthor[i];
						if(authorName[i] == '\0')break;
					}
					//level description
					for (int i = 0;i < 100 ; i++) {
						mapDescription[i] = pointerlevel[i];
						if(mapDescription[i] == '\0')break;
					}
					//rows and cols
					rows[0] = pointerRows[0];
					cols[0] = pointerCols[0];
					for (int i = 0; i < cols[0] * rows[0]; i++) {
						mapArray[i] = buff[i];
						if(i == rows[0] * cols[0] -1){
							mapArray[i + 1] = '\0';
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
					move(5,0);
				}
				break;
			} else if (strcmp(token1, "w") == 0 && token2 != NULL){
				for (int i = 0;; i++) {
					fileName[i] = token2[i];
					if(fileName[i] == '\0')break;
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
				move(5,0);
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
				move(0,0);
				break;
			}else if(strcmp(token1, "n") == 0 && token2 != NULL && token3 != NULL && token4 != NULL){
				for (int i = 0;;i++) {
					fileName[i] = token2[i];
					if(fileName[i] == '\0')break;
				}
				rows[0] = atoi(token3);
				cols[0] = atoi(token4);
				if(atoi(token3) >= 30 || atoi(token4) >= 65 || rows[0] == 0 || cols[0] == 0){
					cleanLastRow();
					getmaxyx(stdscr,h,w);
					move(h-1,0);					
					printw("Invalid rows and cols, 0 < rows <= 30, 0< cols <= 65");
					move(5,0);
					break;
				}
				for (int i = 0; i < rows[0] * cols[0]; i++) {
					mapArray[i] = ' ';
				}
				clear();
				move(0,0);
				printw("File name: %s\n", fileName);
				printw("AuthorName: %s\n", authorName);
				printw("Map level: %s\n", mapDescription);
				printw("Number of Rows: %d\n", rows[0]);
				printw("Number of Cols: %d\n", cols[0]);
				renderMap(mapArray, rows[0], cols[0]);
				cleanLastRow();
				isQuit[0] = 0;
				move(5,0);
				break;
			} else if (strcmp(token1, "ca") == 0 && token2 != NULL){
				//change the author information
				for (int i = 0; ; i++) {
					authorName[i] = buffer[i+3];
					if(authorName[i] == '\0')break;
				}
				clear();
				move(0,0);
				printw("File name: %s\n", fileName);
				printw("AuthorName: %s\n", authorName);
				printw("Map level: %s\n", mapDescription);
				printw("Number of Rows: %d\n", rows[0]);
				printw("Number of Cols: %d\n", cols[0]);
				renderMap(mapArray, rows[0], cols[0]);
				break;
			}else if (strcmp(token1, "cm")== 0 && token2 != NULL){
				//change the map description
				for (int i = 0; ; i++) {
					mapDescription[i] = buffer[i+3];
					if(mapDescription[i] == '\0')break;
				}
				clear();
				move(0,0);
				printw("File name: %s\n", fileName);
				printw("AuthorName: %s\n", authorName);
				printw("Map level: %s\n", mapDescription);
				printw("Number of Rows: %d\n", rows[0]);
				printw("Number of Cols: %d\n", cols[0]);
				renderMap(mapArray, rows[0], cols[0]);
				break;
			} else {
				getmaxyx(stdscr,h,w);
				move(h-1,0);
				printw("Invalid command!");
				move(5,0);
				break;
			}
		} else if (buffer[i] == 27){
			getmaxyx(stdscr,h,w);
			move(h-1,0);
			for (int i = 0 ; i < w; i++) {
				addch(' ');
			}
			move(5,0);
			break;									  
		}
	}
}
char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n * sizeof(char));
    if(dup)
    {
        strcpy(dup, str);
    }
    return dup;
}
