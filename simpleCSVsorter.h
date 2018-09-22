#ifndef SIMPLE_CSV_SORTER_H
#define SIMPLE_CSV_SORTER_H
#define DEBUGGING           "**DEBUGGING**\t"
#define DELIMITER           ","
#define MAX_LINE_LENGTH     512
#define MAX_NUM_RECORDS     20
#define MAX_NUM_COLUMNS     30


/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

struct MovieRecord {
    char *color;
    int number;
    char *animal;
};

void printArguments(int argCount, char *argArray[]);
void printMovieRecords(int count, struct MovieRecord **arrayOfMovieRecords);
void getArrayOfTokens(char **arrayOfTokens, char * line, const char *delimiter);
int getLine(char line[], int maxLength);
void initializeArrayOfMovies(int numberOfRecords, struct MovieRecord **arrayOfMovies);
void mergeSort(int count, struct MovieRecord **sourceArray, struct MovieRecord **outputArray); 
void merge(int count1, struct MovieRecord **tempArray1, int count2, struct MovieRecord **tempArray2, struct MovieRecord **outputArray);
void copyArrayOfMovies(int count, struct MovieRecord **overSizedArray, struct MovieRecord **correctSizeArray);


#endif
