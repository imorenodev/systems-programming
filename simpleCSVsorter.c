#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "simpleCSVsorter.h"


// Struct
struct movieRecord {
    char *color;
    int number;
    char *animal;
};

void printArguments(int argCount, char *argArray[]);
void processInput(struct movieRecord **arrayOfPtrsToMovieRecords);


int main(int argc, char *argv[])
{
    //printArguments(argc, argv);
    
    // initialize array of struct MovieMetaData pointers, initial size is 5 => will dynamically resize as needed
    struct movieRecord *arrMovieRecords = (struct movieRecord *)malloc(sizeof(struct movieRecord)*5);
    if (arrMovieRecords == NULL)
    {
        fprintf(stderr, "Malloc Failed to allocate memory for arrMovieRecords");
        return -1;
    }

    struct movieRecord movieA = { .color = "red", .number = 77, .animal = "goose" };
    arrMovieRecords[0] = movieA;
    printf("movieA: color=%s number=%d animal=%s\n", arrMovieRecords[0].color, arrMovieRecords[0].number, arrMovieRecords[0].animal);

    // create array that holds 5 movieRecord pointers (5 pointers that each point to a movieRecord)
    struct movieRecord **arrayOfPtrsToMovieRecords = (struct movieRecord **)malloc(sizeof(struct movieRecord *)*5);;
    arrayOfPtrsToMovieRecords[0] = &movieA;
    printf("movieA: color=%s number=%d animal=%s\n", arrayOfPtrsToMovieRecords[0]->color, arrayOfPtrsToMovieRecords[0]->number, arrayOfPtrsToMovieRecords[0]->animal);

    // get input from csv
    processInput(arrayOfPtrsToMovieRecords);
    /**
    char *buffer = (char*)malloc(sizeof(char)*2000);
    int lineNumber = 0;

    while (fgets(buffer, 2000, stdin) != NULL)
    {
        if (strcmp(buffer,"\n") != 0)
        {
            arrayOfPtrsToMovieRecords[lineNumber] = (struct movieRecord *)malloc(sizeof(struct movieRecord));
            arrayOfPtrsToMovieRecords[lineNumber]->color = buffer;
            printf("BUFFER:\t%s\n", arrayOfPtrsToMovieRecords[lineNumber]->color);
            lineNumber++;
        }
    }
    
    //printf("BUFFER:\t%s\n", arrMovieRecords[0]->color);

    //processOutput();
    
    free(buffer);
    free(arrayOfPtrsToMovieRecords);
    */
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

void processInput(struct movieRecord **arrayOfPtrsToMovieRecords) 
{
    // get input from csv
    char *buffer = (char*)malloc(sizeof(char)*2000);
    int lineNumber = 0;

    while (fgets(buffer, 2000, stdin) != NULL)
    {
        if (strcmp(buffer,"\n") != 0)
        {
            arrayOfPtrsToMovieRecords[lineNumber] = (struct movieRecord *)malloc(sizeof(struct movieRecord));

            const char *DELIMITER = ",";
            char *stringToken;
            stringToken = strtok(buffer, DELIMITER); 
            while(stringToken != NULL)
            {
                arrayOfPtrsToMovieRecords[lineNumber]->color = stringToken;
                stringToken = strtok(NULL, DELIMITER);
                printf("number: %s\n", stringToken);
                arrayOfPtrsToMovieRecords[lineNumber]->number= atoi(stringToken);
                stringToken = strtok(NULL, DELIMITER);
                arrayOfPtrsToMovieRecords[lineNumber]->animal= stringToken;
                stringToken = strtok(NULL, DELIMITER);
            }
            printf("movieA: color=%s number=%d animal=%s\n", arrayOfPtrsToMovieRecords[lineNumber]->color, arrayOfPtrsToMovieRecords[lineNumber]->number, arrayOfPtrsToMovieRecords[lineNumber]->animal);
            lineNumber++;
        }
    }
    
    free(buffer);
    free(arrayOfPtrsToMovieRecords);

    return;
}


