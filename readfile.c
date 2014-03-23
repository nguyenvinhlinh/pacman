#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
char * readFile(char * fileName,char * authorName, char * mapLevel, int * cols, int * rows){
	FILE * file;
	char filePath[50] = "../levels/";
	//Print input parameter
	printf("%s\n", fileName);
	printf("%s\n", authorName);
	printf("%s\n", mapLevel);
	printf("%d\n", cols[0]);
	printf("%s", filePath);

	//append the filepath with the file name
	//printf("\nAppending\n");
	int i;
	int j = 0;

	for (i = 10; i < 50; i++) {
		filePath[i] = fileName[j];
		if(fileName[j++] == '\0')break;
	}
	//Appending completely
	//printf("File path after appending: %s\n", filePath);
	file = fopen(filePath, "r");
	if(file == NULL){
		printf("Cannot find file.\n");
	  	return NULL;
	} else {		
		//Take information from file and paste it to input pointer
		char buffer[100];
		fgets(buffer, 100, file);
		//Author name
	   	for (i = 0; i < 100; i++) {
			authorName[i] = buffer[i];
			if(buffer[i]== '\0')break;
		}
		//map level info
		fgets(buffer, 100, file);
		for (i = 0; i < 100; i++) {
			mapLevel[i] = buffer[i];
			if(buffer[i]== '\0')break;
		}
		//number of rows and cols. also pasre the value of cols to *cols
		fgets(buffer,100,file);
		rows[0] = atoi(buffer);
		fgets(buffer,100,file);
		cols[0] = atoi(buffer);
		//Take info of map line by line, then push it into array 1D
		char *mapArray = malloc(sizeof(char) * rows[0] * cols[0]);	
		for (i = 0; i < rows[0]; i++) {
			fgets(buffer, 100,file);
			for (j = 0; j < cols[0]; j++) {
				mapArray[cols[0] * i + j] = buffer[j];
			}
		}
		return mapArray;
	}
	//Print input parameter after doing somthing
}
/*
void main(){
	char file[] = "level1.pac";
	char name[100] = "Linh";
	char level[100] = "level1";
	char * fileName = &file[0];
	char * authorName = &name[0];
	char * mapLevel = &level[0];
	int * cols = malloc(sizeof(int) * 1);
	int * rows = malloc(sizeof(int) * 1);
	cols[0] = 0;
	rows[0] = 0;
	char * map = readFile(fileName, authorName, mapLevel, cols, rows);

	printf("File name: %s\n", fileName);
	printf("Author name: %s\n", authorName);
	printf("Map level: %s\n", mapLevel);
	printf("Number of collums: %d\n", cols[0]);
	printf("Number of rows: %d\n", rows[0]);

	int i = 0;
	int j = 0;
	for (i = 0; i < rows[0]; i++) {
		for (j = 0; j < cols[0]; j++) {
			printf("%c", map[cols[0] * i + j]);
		}
		printf("\n");
	}
}
*/
