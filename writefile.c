#include <stdio.h>
#include <stdlib.h>
#include "writefile.h"
void writeFile(char * fileName, char * author, char * mapLevel, int  cols,int  rows, char * mapArray){
	FILE *file;
	char buffer[100];
	//open new file with file name from char pointer fileName
	int i,j;
	for (i = 0; i < 100; i++) {
		buffer[i] = fileName[i];
		if(buffer[i] == '\0'){
			break;
		}
	}
	file = fopen(buffer, "w");
	if(file == NULL){
		printf("Error occurs\n");
	} else {
//read and write the author to file
		
		for (i = 0; i < 100; i++) {
			buffer[i] = author[i];
			if(buffer[i] == '\0'){
				break;
			}
		}
		fprintf(file, "%s\n",buffer);
		
		//read and write mapLevel
		for (i = 0; i < 100; i++) {
			buffer[i] = mapLevel[i];
			if(buffer[i] == '\0'){
				break;
			}
		}
		fprintf(file, "%s\n",buffer);

		//write the number of rows
		fprintf(file, "%d\n",rows );
		//write the number of cols
		fprintf(file, "%d\n",cols);

//write the map array
		printf("row: %d,cols: %d\n", rows, cols);
		for (i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				buffer[cols * i + j] = mapArray[cols * i + j];
				if(j == cols - 1){
					fprintf(file, "%c\n", buffer[cols*i+j]);
				} else {
					fprintf(file, "%c", buffer[cols*i+j]);
				}
				printf("row: %d, col: %d, char:  %c,origin  char %c \n", i, j,  buffer[cols * i + j],mapArray[cols * i +j]);
			}
			
		}
		
		//close file. DONE
		fclose(file);

	}
}
/*
void main(){
	char fileName[] = "NEWFILE.pac";
	char author[100] = "Linh";
	char level[100] = "this is super extreme";	
	char * fileNamePointer = &fileName[0];
	char * authorNamePointer = &author[0];
	char * mapLevelPointer = &level[0];
	int cols = 3;
	int rows = 2;

	
	char * mapArray = malloc(sizeof(char) * cols * rows);
	mapArray[0] = 'a';
	mapArray[1] = 'b';
	mapArray[2] = 'c';
	mapArray[3] = 'd';
	mapArray[4] = 'e';
	mapArray[5] = 'f';
	

	
	writeFile(fileNamePointer, authorNamePointer, mapLevelPointer, cols, rows, mapArray);

	free(mapArray);
}
*/
