#ifndef SIMPLE_CSV_SORTER_H
#define SIMPLE_CSV_SORTER_H
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
void printMovieRecords(struct MovieRecord **arrayOfMovieRecords, int lengthOfArrayOfMovieRecords);
void getArrayOfTokens(char **arrayOfTokens, char * line, const char *delimiter);
int getLine(char line[], int maxLength);

static const char *DEBUGGING = "**DEBUGGING**\t";
static const char *DELIMITER= ",";
static const int MAX_LINE_LENGTH = 512;
static const int MAX_NUM_RECORDS = 20;
static const int MAX_NUM_COLUMNS = 30;


//Suggestion: prototype a mergesort function

#endif
