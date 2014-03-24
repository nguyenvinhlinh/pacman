#include "editcell.h"
void editCell(char * mapArray, int cols, int editCol, int editRow, char editChar){
	mapArray[cols * editRow + editCol] = editChar;
	return 0;
}
