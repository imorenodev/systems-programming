#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simpleCSVsorter.h"


// Struct 
typedef struct {
    char *color;
    int number;
    char *animal;
} MovieRecord;

// Pointer-To-Struct
typedef MovieRecord *pMovieRecord;

void printArguments(int argCount, char *argArray[]);
void processInput(pMovieRecord *arrMovieRecords);


int main(int argc, char *argv[])
{
    //printArguments(argc, argv);
    
    MovieRecord movieA;
    movieA.color = "blue";
    movieA.number = 7;
    movieA.animal = "cat";

    // initialize array of struct MovieMetaData pointers, initial size is 5 => will dynamically resize as needed
    //struct MovieMetaData **arrMovies = (struct MovieMetaData **)malloc(sizeof(struct MovieMetaData)*5);
    pMovieRecord *arrMovieRecords = (pMovieRecord *)malloc(sizeof(pMovieRecord)*5);
    if (arrMovieRecords == NULL)
    {
        fprintf(stderr, "Malloc Failed to allocate memory for arrMovieRecords");
        return -1;
    }
    arrMovieRecords[0] = &movieA;

    // get input from csv
    char *buffer = (char*)malloc(sizeof(char)*2000);
    int lineNumber = 0;

    while (fgets(buffer, 2000, stdin) != NULL)
    {
        if (strcmp(buffer,"\n") != 0)
        {
            //MovieRecord tempMovieRecord = { .color = buffer };
            MovieRecord *tempMovieRecord = (MovieRecord *)malloc(sizeof(MovieRecord));
            tempMovieRecord->color = buffer;
            arrMovieRecords[lineNumber++] = tempMovieRecord;
            printf("BUFFER:\t%s\n", arrMovieRecords[lineNumber-1]->color);
        }
    }
    
    printf("BUFFER:\t%s\n", arrMovieRecords[0]->color);

    //processOutput();
    
    free(buffer);

    return;    
    
    free(arrMovieRecords);
    return 0;
}

void printArguments(int argCount, char *argArray[])
{
    printf("%s Number of Arguments: %d\n", DEBUGGING, argCount);

    for (int i = 0; i < argCount; i++)
    {
        printf("%s Argument %d: %s\n", DEBUGGING, i, argArray[i]);
    }

    return;
}

void processInput(pMovieRecord *arrMovieRecords)
{
    char *buffer = (char*)malloc(sizeof(char)*2000);
    int lineNumber = 0;

    while (fgets(buffer, 2000, stdin) != NULL)
    {
        if (strcmp(buffer,"\n") != 0)
        {
            //MovieRecord tempMovieRecord = { .color = buffer };
            MovieRecord *tempMovieRecord = (MovieRecord *)malloc(sizeof(MovieRecord));
            tempMovieRecord->color = buffer;
            arrMovieRecords[lineNumber++] = tempMovieRecord;
            printf("BUFFER:\t%s\n", arrMovieRecords[lineNumber-1]->color);
        }
    }
    
    printf("BUFFER:\t%s\n", arrMovieRecords[0]->color);

    free(buffer);

    return;
}
