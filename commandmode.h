/** This is command mode
  * @param fileName file name example zxc.pac
  * @param authorName author information including name and email
  * address
  * @param mapDescription the description of map
  * @param rows number of rows
  * @param cols number of columns
  * @param mapArray the map
  * @param isQuit use to track the workflow of program terminated or
  * not 1 - quit, 0 continue
  */
void fullCommandMode(char * fileName, char * authorName, char * mapDescription, int * rows, int * cols, char * mapArray, int * isQuit);
